#include <algorithm>
#include <chrono>
#include <cmath>
#include <thread>
#include <vector>

#include "Elevator.h"

static const int DOOR_DELAY_MS = int(5000);
static const int MOVE_DELAY_MS = int(1000);

class Elevator : public IElevator {
    private:
        int doorDelay;
        int moveDelay;
        int current;

        const State* state;
        const DoorState* doorState;
        const IHeading* heading;
        std::list<const IPassenger *> pendingPassengers;
        std::list<const IPassenger *> boardedPassengers;

    public:

    Elevator(int doorDelayMs = DOOR_DELAY_MS, int moveDelayMs = MOVE_DELAY_MS, int current = 1) :
        doorDelay(doorDelayMs), moveDelay(moveDelayMs), current(current),
        state(IDLE), doorState(DOORS_OPEN), heading(STOPPED), 
        pendingPassengers(), boardedPassengers() {}

    ~Elevator() {
        delete state;
        delete doorState;
        delete heading;
    }

    Elevator(const Elevator& other) :
        doorDelay(other.doorDelay), moveDelay(other.moveDelay), current(other.current), 
        state(other.state), doorState(other.doorState), heading(other.heading),
        pendingPassengers(other.pendingPassengers), boardedPassengers(other.boardedPassengers) {}

    Elevator& operator=(const Elevator&) = delete;

    Elevator(Elevator&& other) noexcept :
        doorDelay(other.doorDelay), moveDelay(other.moveDelay), current(other.current), 
        state(other.state), doorState(other.doorState), heading(other.heading),
        pendingPassengers(other.pendingPassengers), boardedPassengers(other.boardedPassengers) {}

    Elevator& operator=(Elevator&&) = delete;

    const bool IsIdle() const override { return state == IDLE; }
    const int CurrentFloor() const override { return current; }
    
    friend const bool PassedOrigin(const Elevator &, const IPassenger &);
    friend const bool PassedDestination(const Elevator &, const IPassenger &);

    /**
     * The farthest we must go at our current heading before we can change direction
     * Filter all pending passengers that we have not passed -> their Origin
     * Filter all boarded passengers ahead -> their Destination
     */
    friend const double FarthestToGo(const Elevator &);
    friend const bool FurtherToGo(const Elevator &);
    friend const bool Board(Elevator &);
    friend const bool Leave(Elevator &);
    friend const void MoveLoop(Elevator &);
    
   /**
     *  ... weight limit...
     *  ... elevator spread when no passengers no requests ...
    */
    friend const void Move(Elevator &);

    /**
     * Calculate how inconvenient it would be to pick up a passenger. Cases:
     * 1. Same floor, doors opened and either stopped or same direction (0-distance)
     * 2. Stopped; no direction (distance between current floor and passenger's origin)
     * 3. Heading in same direction and away floor (twice distance between current and farthest + distance between current and passenger's origin)
     * 4. Heading in same direction on approach floor (distance between current and passenger's origin)
     * 5. Heading in opposite direction ( distance between farthest and current + distance between farthest and passenger's origin)
     */
    const double Divergence(const IPassenger &passenger) const override {
        // std::cout << "Check ";
        // passenger.print(std::cout);

        if(heading == STOPPED) {
            if(current == passenger.Origin() && doorState == DOORS_OPEN && 
                ( state == IDLE || heading == passenger.Heading() )
            ) {
                return 0;
            }

            if(state == IDLE) {
                return std::abs(current - passenger.Origin());
            }
        }

        if(heading == passenger.Heading()) {
            if(PassedOrigin(*this, passenger)) {
                return 2 * std::abs(current - FarthestToGo(*this)) + std::abs(current - passenger.Origin());
            } else {
                return std::abs(current - passenger.Origin());
            }
        }

        if(heading != passenger.Heading()) {
            double f = FarthestToGo(*this);
            return std::abs(f - current) + std::abs(f - passenger.Origin());
        }

        throw std::invalid_argument("Invalid heading for elevator.");
    }

    const std::future<std::list<const IPassenger *>> ReceivePassenger(const IPassenger &passenger) override {
        return std::async(
            std::launch::async,
            &Elevator::_ReceivePassenger, this, std::ref(passenger)
        );
    }

    std::list<const IPassenger *> _ReceivePassenger(const IPassenger &passenger) {
        if(pendingPassengers.end() == std::find(pendingPassengers.begin(), pendingPassengers.end(), &passenger)) {
            std::cout << "Passenger request ";
            passenger.print(std::cout);
            std::cout << " received." << std::endl;
            pendingPassengers.insert(pendingPassengers.end(), &passenger);
            print(std::cout);
            std::cout << std::endl;
            Move(*this);
        }
        return pendingPassengers;
    }
    
    const std::ostream& print(std::ostream& os) const override {
        os << "Currently at floor " << current << ". ";
        state->print(os);
        os << " ";
        doorState->print(os);
        os << " ";
        heading->print(os);

        if(!boardedPassengers.empty()) {
            os << std::endl << "\t" << boardedPassengers.size() << " boarded passenger(s): ";
            for(auto boardedPassenger = boardedPassengers.begin(); boardedPassenger != std::prev(boardedPassengers.end());) {
                (*boardedPassenger)->print(os);
                os << ", ";
                ++boardedPassenger;
            }
            boardedPassengers.back()->print(os);
        }

        if(!pendingPassengers.empty()) {
            os << std::endl << "\t" << pendingPassengers.size() << " awaiting passenger(s): ";
            for(auto pendingPassenger = pendingPassengers.begin(); pendingPassenger != std::prev(pendingPassengers.end());) {
                (*pendingPassenger)->print(os);
                os << ", ";
                ++pendingPassenger;
            }
            pendingPassengers.back()->print(os);
        }
        return os;
    };
};

const bool PassedOrigin(const Elevator &elevator, const IPassenger &passenger) {
    if(elevator.heading == STOPPED) { return false; }
    return elevator.heading == GOING_DOWN && passenger.Origin() > elevator.current || elevator.heading == GOING_UP && passenger.Origin() < elevator.current;
}

const bool PassedDestination(const Elevator &elevator, const IPassenger &passenger) {
    if(elevator.heading == STOPPED) { return false; }
    return elevator.heading == GOING_DOWN && passenger.Destination() > elevator.current || elevator.heading == GOING_UP && passenger.Destination() < elevator.current;
}

const double FarthestToGo(const Elevator &elevator) {
    std::list<double> forwardStops;
    for(const auto& pendingPassenger : elevator.pendingPassengers) {
        if(!PassedOrigin(elevator, *pendingPassenger)) {
            forwardStops.push_back(pendingPassenger->Origin());
        }
    }
    for(const auto& boardedPassenger : elevator.boardedPassengers) {
        if(!PassedDestination(elevator, *boardedPassenger)) {
            forwardStops.push_back(boardedPassenger->Destination());
        }
    }
    if(elevator.heading == GOING_UP) {
        return *std::max_element(forwardStops.begin(), forwardStops.end());
    } else {
        return *std::min_element(forwardStops.begin(), forwardStops.end());
    }
    return 0;
}

const bool FurtherToGo(const Elevator &elevator) {
    if(elevator.heading == STOPPED) { return false; }
    if(elevator.boardedPassengers.empty()) {
        for(const auto& pendingPassenger : elevator.pendingPassengers) {
            if(elevator.heading != pendingPassenger->Heading()) { continue; }
            if(elevator.heading == GOING_UP && pendingPassenger->Origin() > elevator.current) { return true; }
            if(elevator.heading == GOING_DOWN && pendingPassenger->Origin() < elevator.current) { return true; }
        }
    }
    for(const auto& boardedPassenger : elevator.boardedPassengers) {
        if(elevator.heading == GOING_UP && boardedPassenger->Destination() > elevator.current) { return true; }
        if(elevator.heading == GOING_DOWN && boardedPassenger->Destination() < elevator.current) { return true; }
    }
    return false;
}

const bool Board(Elevator &elevator) {
    bool board = false;
    if(!elevator.pendingPassengers.empty()) {
        for(auto passenger = elevator.pendingPassengers.begin(); passenger != elevator.pendingPassengers.end();) {
            if(elevator.current == (*passenger)->Origin() && (elevator.heading == STOPPED || elevator.heading == (*passenger)->Heading())) {
                std::cout << "Passenger ";
                (*passenger)->print(std::cout);
                std::cout << " is boarding. " << std::endl;
                elevator.boardedPassengers.push_back(*passenger);
                passenger = elevator.pendingPassengers.erase(passenger);
                board = true;
            } else {
                ++passenger;
            }
        }
    }
    return board;
}

const bool Leave(Elevator &elevator) {
    bool leave = false;
    if(!elevator.boardedPassengers.empty()) {
        for(auto boardedPassenger = elevator.boardedPassengers.begin(); boardedPassenger != elevator.boardedPassengers.end();) {
            if(elevator.current == (*boardedPassenger)->Destination()) {
                std::cout << std::endl << "Passenger ";
                (*boardedPassenger)->print(std::cout);
                std::cout << " is leaving." << std::endl;
                boardedPassenger = elevator.boardedPassengers.erase(boardedPassenger);
                leave = true;
            } else {
                ++boardedPassenger;
            }
        }
    }
    return leave;
}

const void MoveLoop(Elevator &elevator) {
    bool board = Board(elevator);
    bool depart = Leave(elevator);

    if(elevator.pendingPassengers.empty() && elevator.boardedPassengers.empty()) {
        elevator.heading = STOPPED;
    }

    if(board || depart) {
        std::cout << "An elevator is currently servicing floor " << elevator.current << std::endl;
        elevator.doorState = DOORS_OPENING;
        std::cout << "Doors opening..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(elevator.doorDelay)); // Simulate door opening time
        elevator.doorState = DOORS_OPEN;
    }
    
    if(elevator.pendingPassengers.empty() && elevator.boardedPassengers.empty()) {
        elevator.state = IDLE;
        std::cout << "Elevator has come to a halt." << std::endl;
    } else if(elevator.doorState == DOORS_OPEN) {
        elevator.doorState = DOORS_CLOSING;
        std::this_thread::sleep_for(std::chrono::milliseconds(elevator.doorDelay)); // Simulate door closing time
        elevator.doorState = DOORS_CLOSED;
        std::cout << "Doors closed." << std::endl;
    } else if(!FurtherToGo(elevator)) {
        elevator.heading = elevator.heading == GOING_UP ? GOING_DOWN : GOING_UP;
    }

    if(elevator.heading == GOING_UP) {
        std::this_thread::sleep_for(std::chrono::milliseconds(elevator.moveDelay)); // Simulate time taken to move one floor
        ++elevator.current;
    }
    if(elevator.heading == GOING_DOWN) {
        std::this_thread::sleep_for(std::chrono::milliseconds(elevator.moveDelay)); // Simulate time taken to move one floor
        --elevator.current;
    }
}

/**
 * not thread safe.
 */
const void Move(Elevator &elevator) {
    if(elevator.state == ACTIVE) { return; }
    std::thread t([&]() {
        elevator.state = ACTIVE;
        while(!elevator.pendingPassengers.empty() || !elevator.boardedPassengers.empty()) {
            MoveLoop(elevator);
        }
    });
    t.detach();
}