#include <chrono>
#include <cmath>
#include <thread>
#include <vector>

#include "Elevator.h"

class Idle : public State {
public:
    std::ostream& Printout(std::ostream& os) const override {
        os << "Elevator is idle.";
        return os;
    }
};
class Active : public State {
public:
    std::ostream& Printout(std::ostream& os) const override {
        os << "Elevator is moving.";
        return os;
    }
};
static const Idle* IDLE = new Idle();
static const Active* ACTIVE = new Active();

class DoorsOpen : public DoorState {
public:
    std::ostream& Printout(std::ostream& os) const override {
        os << "Doors are open.";
        return os;
    }
};
class DoorsClosed : public DoorState {
public:
    std::ostream& Printout(std::ostream& os) const override {
        os << "Doors are closed.";
        return os;
    }
};
static const DoorsOpen* DOORS_OPEN = new DoorsOpen();
static const DoorsClosed* DOORS_CLOSED = new DoorsClosed();

class Stopped : public IHeading {
public:
    std::ostream& Printout(std::ostream& os) const override {
        os << "Stopped.";
        return os;
    }
};
static const Stopped* STOPPED = new Stopped();

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
        std::unordered_set<int> requests;

    public:

    Elevator(int doorDelay = DOOR_DELAY, int moveDelay = MOVE_DELAY)
           : doorDelay(doorDelay), moveDelay(moveDelay), current(1), state((State*)IDLE), doorState((DoorState*)DOORS_OPEN), heading((IHeading*)STOPPED), passengers(), requests() {}
    
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

    friend std::ostream& operator<<(std::ostream&, const Elevator&);

    bool IsIdle() override { return state == IDLE; }
    int CurrentFloor() { return current; }

    /**
     *  ... weight limit...
     *  ... elevator spread when no passengers no requests ...
     *
    /

    /*
     *  same floor same direction
     *      win
     * 
     *  stopped
     *      distance to origin
     * 
     *      
     * 
     *  different floor same direction within
     *      distance = abs (current floor - embark floor)
     *  different floor same direction further out
     *      distance = abs (current floor - disembark floor)
     * 
     *  same floor different direction
     *      distance = 2 * farthest distance + opposite distance
     * 
     *  different floor different direction
     *      distance = 2 * abs (current floor - farthest floor)
     *                  + abs (disembark floor - farthest floor)
     * 
     */

    double Divergence(const IPassenger& passenger) const override {
        if(doorState == DOORS_OPEN && current == passenger.Origin() && heading == passenger.Heading()) {
            return 0;
        }
        const int passengerDistance = std::abs(current - passenger.Origin());
        if(state == IDLE) {
            return std::abs(current - passenger.Origin());
        }
        if(heading == passenger.Heading() && passenger.AlongTheWay(current)) {
            return std::abs(current - passenger.Origin());
        } else {
            IPassenger* farthestPassenger;
            int farthestDistance;
            for(const auto& somePassenger : passengers) {
                if(farthestPassenger == nullptr) {
                    farthestPassenger = somePassenger;

                }
            }
        }
        

        return 0.0;
    }

    std::unordered_set<IPassenger*> ReceivePassenger(const IPassenger& passenger) override {
        throw std::logic_error("not yet implemented");
        // return std::unordered_set<Passenger>();
        // passenger->origin();
        // passenger.origin();
        // if(current == passenger.origin()) {

        // }
    }

    std::unordered_set<int> RequestFloor(const int& floor) {
        throw std::logic_error("not yet implemented");

        // if(current == floor) {
        //     return requests;
        // }
        // auto search = requests.find(floor);
        // if(search != requests.end()) {
        //     return requests;
        // } 
        // requests.insert(floor);
        // Move();
        // return requests;
    }
    protected:
    void Move() override {
        throw std::logic_error("not yet implemented");

        if(state == ACTIVE) { return; }
        std::thread t([this]() {

            state = (Active*)ACTIVE;
            while(!requests.empty()) {
                auto search = requests.find(current);
                if(search != requests.end()) {
                    requests.erase(*search);
                    std::this_thread::sleep_for(std::chrono::milliseconds(doorDelay)); // Simulate door opening time
                    doorState = (DoorsOpen*)DOORS_OPEN;
                }
                if(heading == STOPPED) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(doorDelay)); // Simulate door closing time
                    doorState = (DoorsClosed*)DOORS_CLOSED;
                    int dest = *requests.begin();
                    int dist = dest - current;
                    for(const int& p : requests) {
                        if(std::abs(p - current) < std::abs(dist)) {
                            dest = p;
                            dist = p - current;
                        }
                    }
                    if(dist > 0) {
                        heading = (GoingUp*)GOING_UP;
                    } else if(dist == 0) {
                        heading = (Stopped*)STOPPED;
                    } else {
                        heading = (GoingDown*)GOING_DOWN;
                    }
                }
                if(requests.empty()) {
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
};
std::ostream& operator<<(std::ostream& os, const Elevator& elevator) {
    os << "\tElevator is currently at floor " << elevator.current << ". ";
    elevator.state->Printout(os);
    os << " ";
    elevator.doorState->Printout(os);
    os << " ";
    elevator.heading->Printout(os);
    if(!elevator.requests.empty()) {
        os << " Requested floor(s): " << std::endl;
        std::vector<int> as_vector(elevator.requests.begin(), elevator.requests.end());
        for(int i = 0; i < as_vector.size() - 1; ++i) {
            os << as_vector.at(i) << ", ";
        }
        os << as_vector.back();
    }
    return os;
};