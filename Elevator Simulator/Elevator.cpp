#include <algorithm>
#include <chrono>
#include <cmath>
#include <thread>

#include "Elevator.h"

static const int DOOR_DELAY = int(300);
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

    public:

    Elevator(int doorDelay = DOOR_DELAY, int moveDelay = MOVE_DELAY)
           : doorDelay(doorDelay), moveDelay(moveDelay), current(1), state((State*)IDLE), doorState((DoorState*)DOORS_OPEN), heading((IHeading*)STOPPED), passengers() {}

    const bool IsIdle() const override { return state == IDLE; }
    const int CurrentFloor() const override { return current; }

    const double Divergence(const IPassenger &passenger) const override {
        // std::cout << "Check ";
        // passenger.print(std::cout);
        if(doorState == DOORS_OPEN && current == passenger.Origin() && heading == passenger.Heading()) {
            return 0;
        }
        const int passengerDistance = std::abs(current - passenger.Origin());
        if(state == IDLE) {
            return passengerDistance;
        }

        if(Passed(passenger)) {
            return 2 * FarthestAhead() + passengerDistance;
        }
        // std::cout << "Checked.";
        return passengerDistance;
    }

    const std::vector<const IPassenger *> ReceivePassenger(const IPassenger &passenger) override {
        passengers.push_back(&passenger);
        if(&passenger == passengers.back()) { 
            Move();
        }
        return passengers;
    }

    private:

    const double FarthestAhead() const {
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
   /**
     *  ... weight limit...
     *  ... elevator spread when no passengers no requests ...
    */

    IHeading* ClosestHeading() {
        if(passengers.empty()) { return (Stopped*)STOPPED; }
        IHeading* closestHeading = (Stopped*)STOPPED;
        std::vector<int> origins(passengers.size());
        std::transform(
            passengers.begin(), passengers.end(),
            origins.begin(), 
            [this](const auto& passenger) { return passenger->Origin() - current; }
        );
        int closest = origins.at(0);
        for(const auto& origin : origins) {
            if(std::abs(origin) < std::abs(closest)) {
                closest = origin;
            }
        }
        return (closest > 0) ? (IHeading*) GOING_UP : (IHeading*) GOING_DOWN;
    }

    const void Move() {
        if(state == ACTIVE) { return; }
        std::cout << "We have movement." << std::endl;
        state = (Active*)ACTIVE;
        while(!passengers.empty()) {
            // std::cout << "Found a pass" << std::endl;
            bool del = false;
            for(auto passenger = passengers.begin(); passenger != passengers.end();) {
                if(current == (*passenger)->Destination()) {
                    passengers.erase(passenger);
                    del = true;
                } else {
                    ++passenger;
                }
            }
            if(del) {
                std::this_thread::sleep_for(std::chrono::milliseconds(doorDelay)); // Simulate door opening time
                doorState = (DoorsOpen*)DOORS_OPEN;
            }
            if(heading == STOPPED) {
                std::this_thread::sleep_for(std::chrono::milliseconds(doorDelay)); // Simulate door closing time
                heading = ClosestHeading();
            }
            if(passengers.empty()) {
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
        std::cout << "Moved!!!";
        // std::thread t([&]() {
        //         std::cout << "We have movement." << std::endl;
        //         state = (Active*)ACTIVE;
        //         while(!passengers.empty()) {
        //             std::cout << "Found a pass" << std::endl;
        //             int currentNumPassengers = passengers.size();
        //             auto arrivals = std::find_if(
        //                 passengers.begin(),
        //                 passengers.end(), 
        //                 [&](auto passenger){ return current == passenger->Destination(); }
        //             );
        //             passengers.erase(arrivals);
        //             if(passengers.size() != currentNumPassengers) {
        //                 std::this_thread::sleep_for(std::chrono::milliseconds(doorDelay)); // Simulate door opening time
        //                 doorState = (DoorsOpen*)DOORS_OPEN;
        //             }
        //             if(heading == STOPPED) {
        //                 std::this_thread::sleep_for(std::chrono::milliseconds(doorDelay)); // Simulate door closing time
        //             }
        //             if(passengers.empty()) {
        //                 state = (Idle*)IDLE;
        //                 heading = (Stopped*)STOPPED;
        //             }
        //             if(heading == GOING_UP) {
        //                 std::this_thread::sleep_for(std::chrono::milliseconds(moveDelay)); // Simulate time taken to move one floor
        //                 ++current;
        //             }
        //             if(heading == GOING_DOWN) {
        //                 std::this_thread::sleep_for(std::chrono::milliseconds(moveDelay)); // Simulate time taken to move one floor
        //                 --current;
        //             }
        //         }
        //         std::cout << "Moved!!!";
        //         return;
        //     }
        // );
        // t.detach();
    }

    const std::ostream& print(std::ostream& os) const override {
        os << "Currently at floor " << current << ". ";
        state->Printout(os);
        os << " ";
        doorState->Printout(os);
        os << " ";
        heading->Printout(os);
        if(!passengers.empty()) {
            os << " Passengers:" << std::endl;
            // std::vector<IPassenger*> as_vector(passengers.begin(), passengers.end());
            for(auto itr = passengers.begin(); itr < passengers.end() - 1; ++itr)
            for(int i = 0; i < passengers.size() - 1; ++i) {
                passengers.at(i)->print(os);
                os << ",\n";
            }
            passengers.back()->print(os);
        }
        return os;
    };
};