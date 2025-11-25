#include <algorithm>
#include <chrono>
#include <cmath>
#include <thread>

#include "Elevator.h"

static const int DOOR_DELAY = int(3000);
static const int MOVE_DELAY = int(500);

class Elevator : public IElevator {
    private:
        int doorDelay;
        int moveDelay;
        int current;

        State* state;
        DoorState* doorState;
        IHeading* heading;
        std::vector<const IPassenger *> passengers;
        std::vector<const IPassenger *> boardedPassengers;

    public:

    Elevator(int doorDelay = DOOR_DELAY, int moveDelay = MOVE_DELAY) :
        doorDelay(doorDelay), moveDelay(moveDelay), 
        current(1), state((State*)IDLE), doorState((DoorState*)DOORS_OPEN), heading((IHeading*)STOPPED), 
        passengers(), boardedPassengers(std::vector<const IPassenger*>()) {}

    const bool IsIdle() const override { return state == IDLE; }
    const int CurrentFloor() const override { return current; }

    const double Divergence(const IPassenger &passenger) const override {
        // std::cout << "Check ";
        // passenger.print(std::cout);
        if(doorState == DOORS_OPEN && current == passenger.Origin() && heading == passenger.Heading()) {
            return 0;
        }
        if(state == IDLE) {
            return std::abs(current - passenger.Origin());
        }

        if(Passed(passenger)) {
            return 2 * FurthestAhead() + std::abs(current - passenger.Origin());
        }
        if(heading == passenger.Heading()) {
            std::cout << "Going my way darling." << std::endl;
            return std::abs(current - passenger.Origin());
        } else {
            return
                std::abs(passenger.Origin() - passenger.Destination()) + 
                std::abs(current - passenger.Origin());
        }
    }

    const std::vector<const IPassenger *> ReceivePassenger(const IPassenger &passenger) override {
        if(passengers.end() == std::find(passengers.begin(), passengers.end(), &passenger)) {
            std::cout << "Passenger request ";
            passenger.print(std::cout);
            std::cout << " received." << std::endl;
            // passengers.push_back(&passenger);
            passengers.insert(passengers.end(), &passenger);
            std::cout << "Currently: ";
            print(std::cout);
            std::cout << std::endl;
            Move();
        }
        return passengers;
    }

    private:

   /**
     *  ... weight limit...
     *  ... elevator spread when no passengers no requests ...
    */

    const double FurthestAhead() const {
        std::vector<const IPassenger *> forwards;
        for(const auto passenger : passengers) {
            const auto op = Passed(*passenger);
            if(!op) {
                forwards.push_back(passenger);
            }
        }
        auto firstForward = forwards.at(0);
        int farthest;
        if(heading == firstForward->Heading()) {
            farthest = std::abs(current - firstForward->Destination());
        } else {
            farthest = std::abs(current - firstForward->Origin());
        }

        for(const auto& somePassenger : forwards) {
            if(heading == somePassenger->Heading()) {
                farthest = std::max(
                    farthest, 
                    std::abs(current - somePassenger->Destination())
                );
            } else {
                farthest = std::max(
                    farthest, 
                    std::abs(current - somePassenger->Origin())
                );
            }
        }
        return farthest;
    }

    const bool Passed(const IPassenger &passenger) const {
        return heading == GOING_DOWN && passenger.Origin() > current || heading == GOING_UP && passenger.Origin() < current;
    }

    IHeading* ClosestHeading() {
        if(passengers.empty() && boardedPassengers.empty()) { return (Stopped*)STOPPED; }
        int closestRelative;
        if(!boardedPassengers.empty()) {
            IHeading* closestHeading = (Stopped*)STOPPED;
            closestRelative = boardedPassengers.at(0)->Destination() - current;
            for(const auto& boardedPassenger : boardedPassengers) {
                if(std::abs(closestRelative) > std::abs(boardedPassenger->Destination())) {
                    closestRelative = boardedPassenger->Origin();
                }
            }
        } else {
            IHeading* closestHeading = (Stopped*)STOPPED;
            closestRelative = passengers.at(0)->Origin() - current;
            for(const auto& passenger : passengers) {
                if(std::abs(closestRelative) > std::abs(passenger->Origin())) {
                    closestRelative = passenger->Origin();
                }
            }
        }
        return (closestRelative > 0) ? (IHeading*) GOING_UP : (IHeading*) GOING_DOWN;
    }

    const void Move() {
        if(state == ACTIVE) { return; }
        std::thread t([&]() {
            // std::cout << "We have movement." << std::endl;
            state = (Active*)ACTIVE;
            while(!passengers.empty() || !boardedPassengers.empty()) {
                // std::cout << "Found a pass" << std::endl;
                bool alight = false;
                for(auto boardedPassenger = boardedPassengers.begin(); boardedPassenger != boardedPassengers.end();) {
                    if(current == (*boardedPassenger)->Destination()) {
                        std::cout << std::endl;
                        (*boardedPassenger)->print(std::cout);
                        std::cout << " has gotten off." << std::endl;
                        passengers.erase(boardedPassenger);
                        alight = true;
                    } else {
                        ++boardedPassenger;
                    }
                }
                bool board = false;
                for(auto passenger = passengers.begin(); passenger != passengers.end();) {
                    if(current == (*passenger)->Origin()) {
                        std::cout << std::endl;
                        (*passenger)->print(std::cout);
                        std::cout << " has boarded." << std::endl;
                        boardedPassengers.push_back(*passenger);
                        passengers.erase(passenger);
                        board = true;
                    } else {
                        ++passenger;
                    }
                }
                
                if(board || alight) {
                    std::cout << "An elevator is currently servicing floor " << current << std::endl;
                    std::cout << "Doors opening... ";
                    std::this_thread::sleep_for(std::chrono::milliseconds(doorDelay)); // Simulate door opening time
                    doorState = (DoorsOpen*)DOORS_OPEN;
                    
                    std::this_thread::sleep_for(std::chrono::milliseconds(doorDelay)); // Simulate door closing time
                    doorState = (DoorsClosed*)DOORS_CLOSED;
                    std::cout << "Doors closed." << std::endl;
                }
                if(heading == STOPPED) {
                    heading = ClosestHeading();
                    std::cout << "Elevator has picked direction ";
                    heading->print(std::cout);
                    std::cout << "." << std::endl;
                }
                if(passengers.empty() && boardedPassengers.empty()) {
                    std::cout << "Elevator has come to a halt." << std::endl;
                    state = (Idle*)IDLE;
                    heading = (Stopped*)STOPPED;
                }
                if(heading == GOING_UP) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(moveDelay)); // Simulate time taken to move one floor
                    ++current;
                }
                if(heading == GOING_DOWN) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(moveDelay)); // Simulate time taken to move one floor
                    --current;
                }
            }
            // std::cout << "Moved!!!";
        });
        t.detach();
    }

    const std::ostream& print(std::ostream& os) const override {
        os << "Currently at floor " << current << ". ";
        state->print(os);
        os << " ";
        doorState->print(os);
        os << " ";
        heading->print(os);

        if(!passengers.empty()) {
            os << std::endl << "\t" << passengers.size() << " awaiting passenger(s): ";
            for(int i = 0; i < passengers.size() - 1; ++i) {
                passengers.at(i)->print(os);
                os << ", ";
            }
            passengers.back()->print(os);
        }

        if(!boardedPassengers.empty()) {
            os << std::endl << "\t" << boardedPassengers.size() << " boarded passenger(s): ";
            for(int i = 0; i < boardedPassengers.size() - 1; ++i) {
                boardedPassengers.at(i)->print(os);
                os << ", ";
            }
            boardedPassengers.back()->print(os);
        }
        return os;
    };
};