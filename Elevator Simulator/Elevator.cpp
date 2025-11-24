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
        std::unordered_set<IPassenger*> passengers;

    public:

    Elevator(int doorDelay = DOOR_DELAY, int moveDelay = MOVE_DELAY)
           : doorDelay(doorDelay), moveDelay(moveDelay), current(1), state((State*)IDLE), doorState((DoorState*)DOORS_OPEN), heading((IHeading*)STOPPED), passengers() {}
    
    // ~Elevator() {}

    // Elevator(const Elevator& other) : doorDelay(other.doorDelay), moveDelay(other.moveDelay), current(other.current), state(other.state), doorState(other.doorState), heading(other.heading), passengers(other.passengers), requests(other.requests) {}
    
    // Elevator& operator=(const Elevator& other) {
    //     if (this != &other) {
    //         doorDelay = other.doorDelay;
    //         moveDelay = other.moveDelay;
    //         current = other.current;
    //         state = other.state;
    //         doorState = other.doorState;
    //         heading = other.heading;
    //         passengers = other.passengers;
    //         requests = other.requests;
    //     }
    //     return *this;
    // }

    // Elevator(Elevator&& other) noexcept
    //         : doorDelay(other.doorDelay), moveDelay(other.moveDelay), current(other.current), state(other.state), doorState(other.doorState), heading(other.heading), passengers(other.passengers), requests(other.requests) {}

    // Elevator& operator=(Elevator&& other) noexcept {
    //     if (this != &other) {
    //         doorDelay = other.doorDelay;
    //         moveDelay = other.moveDelay;
    //         current = other.current;
    //         state = other.state;
    //         doorState = other.doorState;
    //         heading = other.heading;
    //         passengers = other.passengers;
    //         requests = other.requests;
    //     }
    //     return *this;
    // }


    const bool IsIdle() override { return state == IDLE; }
    const int CurrentFloor() override { return current; }

    const double Divergence(IPassenger* passenger) override {
        std::cout << "Check " << &passenger;
        if(doorState == DOORS_OPEN && current == passenger->Origin() && heading == passenger->Heading()) {
            return 0;
        }

        const int passengerDistance = std::abs(current - passenger->Origin());
        if(state == IDLE) {
            return passengerDistance;
        }

        if(Passed(passenger)) {
            return 2 * FarthestAhead() + passengerDistance;
        }

        return passengerDistance;
    }

    const std::unordered_set<IPassenger*> ReceivePassenger(IPassenger* passenger) override {
        if(passengers.insert(passenger).second) { Move(); }
        return passengers;
    }

    private:

    const double FarthestAhead() const {
        std::vector<IPassenger*> forwards;
        for(const auto& passenger : passengers) {
            if(!Passed(passenger)) {
                forwards.push_back(passenger);
            }
        }
        IPassenger* firstForward = forwards.at(0);
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

    bool Passed(IPassenger* passenger) const {
        return heading == GOING_DOWN && passenger->Origin() > current || heading == GOING_UP && passenger->Origin() < current;
    }

    void Move() {
        if(state == ACTIVE) { return; }
        std::thread t([&]() {
            state = (Active*)ACTIVE;
            while(!passengers.empty()) {
                int currentNumPassengers = passengers.size();
                auto arrivals = std::find_if(
                    passengers.begin(),
                    passengers.end(), 
                    [&](auto passenger){ return current == passenger->Destination(); }
                );
                passengers.erase(arrivals);
                if(passengers.size() != currentNumPassengers) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(doorDelay)); // Simulate door opening time
                    doorState = (DoorsOpen*)DOORS_OPEN;
                }
                if(heading == STOPPED) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(doorDelay)); // Simulate door closing time
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
            return;
        });
        t.detach();
    }

    friend std::ostream& operator<<(std::ostream&, const Elevator&);
};
std::ostream& operator<<(std::ostream& os, const Elevator& elevator) {
    os << "\tCurrently at floor " << elevator.current << ". ";
    elevator.state->Printout(os);
    os << " ";
    elevator.doorState->Printout(os);
    os << " ";
    elevator.heading->Printout(os);
    if(!elevator.passengers.empty()) {
        os << " Passengers:" << std::endl;
        std::vector<IPassenger*> as_vector(elevator.passengers.begin(), elevator.passengers.end());
        for(int i = 0; i < as_vector.size() - 1; ++i) {
            os << as_vector.at(i) << ", ";
        }
        os << as_vector.back();
    }
    return os;
};