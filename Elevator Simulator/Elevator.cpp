#include <algorithm>
#include <chrono>
#include <cmath>
#include <thread>
#include <vector>

#include "Elevator.h"

static const int DOOR_DELAY = int(5);
static const int MOVE_DELAY = int(1);

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

    Elevator(int doorDelay = DOOR_DELAY, int moveDelay = MOVE_DELAY, int current = 1) :
        doorDelay(doorDelay), moveDelay(moveDelay), current(current),
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
            if(PassedOrigin(passenger)) {
                return 2 * std::abs(current - FarthestToGo()) + std::abs(current - passenger.Origin());
            } else {
                return std::abs(current - passenger.Origin());
            }
        }

        if(heading != passenger.Heading()) {
            double f = FarthestToGo();
            return std::abs(f - current) + std::abs(f - passenger.Origin());
        }

        throw std::invalid_argument("Invalid heading for elevator.");
    }

    const std::list<const IPassenger *> ReceivePassenger(const IPassenger &passenger) override {
        if(pendingPassengers.end() == std::find(pendingPassengers.begin(), pendingPassengers.end(), &passenger)) {
            std::cout << "Passenger request ";
            passenger.print(std::cout);
            std::cout << " received." << std::endl;
            pendingPassengers.insert(pendingPassengers.end(), &passenger);
            if(heading == STOPPED) {
                if(current != passenger.Origin()) {
                    heading = passenger.Origin() > current ? GOING_UP : GOING_DOWN;
                } else {
                    heading = passenger.Destination() > current ? GOING_UP : GOING_DOWN;
                }
            }
            print(std::cout);
            std::cout << std::endl;
            Move();
        }
        return pendingPassengers;
    }

    private:
    
    const bool PassedOrigin(const IPassenger &passenger) const {
        return heading == GOING_DOWN && passenger.Origin() > current || heading == GOING_UP && passenger.Origin() < current;
    }
    const bool PassedDestination(const IPassenger &passenger) const {
        return heading == GOING_DOWN && passenger.Destination() > current || heading == GOING_UP && passenger.Destination() < current;
    }

   /**
     *  ... weight limit...
     *  ... elevator spread when no passengers no requests ...
    */

    /**
     * The farthest we must go at our current heading before we can change direction
     * Filter all pending passengers that we have not passed -> their Origin
     * Filter all boarded passengers ahead -> their Destination
     */
    const double FarthestToGo() const {
        std::list<double> forwardStops;
        for(const auto& pendingPassenger : pendingPassengers) {
            if(!PassedOrigin(*pendingPassenger)) {
                forwardStops.push_back(pendingPassenger->Origin());
            }
        }
        for(const auto& boardedPassenger : boardedPassengers) {
            if(!PassedDestination(*boardedPassenger)) {
                forwardStops.push_back(boardedPassenger->Destination());
            }
        }
        if(heading == GOING_UP) {
            return *std::max_element(forwardStops.begin(), forwardStops.end());
        } else {
            return *std::min_element(forwardStops.begin(), forwardStops.end());
        }
        return 0;
    }

    const bool FurtherToGo() const {
        if(boardedPassengers.empty()) {
            for(const auto& pendingPassenger : pendingPassengers) {
                if(heading != pendingPassenger->Heading()) { continue; }
                if(heading == GOING_UP && pendingPassenger->Origin() > current) { return true; }
                if(heading == GOING_DOWN && pendingPassenger->Origin() < current) { return true; }
            }
        }
        for(const auto& boardedPassenger : boardedPassengers) {
            if(heading == GOING_UP && boardedPassenger->Destination() > current) { return true; }
            if(heading == GOING_DOWN && boardedPassenger->Destination() < current) { return true; }
        }
        return false;
    }
 
    /**
     * not thread safe.
     */
    const void Move() {
        if(state == ACTIVE) { return; }
        std::thread t([&]() {
            state = ACTIVE;
            while(!pendingPassengers.empty() || !boardedPassengers.empty()) {
                MoveLoop();
            }
        });
        t.detach();
    }

    const bool Board() {
        bool board = false;
        if(!pendingPassengers.empty()) {
            for(auto& passenger = pendingPassengers.begin(); passenger != pendingPassengers.end();) {
                if(current == (*passenger)->Origin() && heading == (*passenger)->Heading()) {
                    std::cout << "Passenger ";
                    (*passenger)->print(std::cout);
                    std::cout << " is boarding. " << std::endl;
                    boardedPassengers.push_back(*passenger);
                    passenger = pendingPassengers.erase(passenger);
                    board = true;
                } else {
                    ++passenger;
                }
            }
        }
        return board;
    }

    const bool Depart() {
        bool alight = false;
        if(!boardedPassengers.empty()) {
            for(auto& boardedPassenger = boardedPassengers.begin(); boardedPassenger != boardedPassengers.end();) {
                if(current == (*boardedPassenger)->Destination()) {
                    std::cout << std::endl << "Passenger ";
                    (*boardedPassenger)->print(std::cout);
                    std::cout << " is departing." << std::endl;
                    boardedPassenger = boardedPassengers.erase(boardedPassenger);
                    alight = true;
                } else {
                    ++boardedPassenger;
                }
            }
        }
        return alight;
    }

    const void MoveLoop() {
        bool board = Board();
        bool depart = Depart();

        if(board || depart) {
            std::cout << "An elevator is currently servicing floor " << current << std::endl;
            std::cout << "Doors opening..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(doorDelay)); // Simulate door opening time
            doorState = DOORS_OPEN;
        }
        
        if(pendingPassengers.empty() && boardedPassengers.empty()) {
            state = IDLE;
            heading = STOPPED;
            std::cout << "Elevator has come to a halt." << std::endl;
        } else if(doorState == DOORS_OPEN) {
            std::this_thread::sleep_for(std::chrono::seconds(doorDelay)); // Simulate door closing time
            doorState = DOORS_CLOSED;
            std::cout << "Doors closed." << std::endl;
        }

        if(heading == GOING_UP) {
            std::this_thread::sleep_for(std::chrono::seconds(moveDelay)); // Simulate time taken to move one floor
            ++current;
        }
        if(heading == GOING_DOWN) {
            std::this_thread::sleep_for(std::chrono::seconds(moveDelay)); // Simulate time taken to move one floor
            --current;
        }

        if(!FurtherToGo()) {
            heading = heading == GOING_UP ? GOING_DOWN : GOING_UP;
        }
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
            for(auto& boardedPassenger = boardedPassengers.begin(); boardedPassenger != std::prev(boardedPassengers.end());) {
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