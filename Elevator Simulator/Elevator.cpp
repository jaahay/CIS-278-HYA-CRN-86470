#include "Elevator.h"
#include "Panel.h"
#include "Passenger.h"

#include <chrono>
#include <thread>
#include <vector>

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

class Stopped : public Heading {
public:
    std::ostream& Printout(std::ostream& os) const override {
        os << "Stopped.";
        return os;
    }
};
class GoingUp : public Heading {
public:
    std::ostream& Printout(std::ostream& os) const override {
        os << "Going up.";
        return os;
    }
};
class GoingDown : public Heading {
public:
    std::ostream& Printout(std::ostream& os) const override {
        os << "Going down.";
        return os;
    }
};
static const Stopped* STOPPED = new Stopped();
static const GoingUp* GOING_UP = new GoingUp();
static const GoingDown* GOING_DOWN = new GoingDown();

static const int DOOR_DELAY = int(300);
static const int MOVE_DELAY = int(500);
class Elevator : public IElevator {
    private:
        int doorDelay;
        int moveDelay;
        int current;

        State* state;
        DoorState* doorState;
        Heading* heading;
        std::unordered_set<int> requests;

    public:

    Elevator(int doorDelay = DOOR_DELAY, int moveDelay = MOVE_DELAY)
           : doorDelay(doorDelay), moveDelay(moveDelay), current(1), state((State*)IDLE), doorState((DoorState*)DOORS_OPEN), heading((Heading*)STOPPED), requests() {}
    
    ~Elevator() {}

    Elevator(const Elevator& other) : doorDelay(other.doorDelay), moveDelay(other.moveDelay), current(other.current), state(other.state), doorState(other.doorState), heading(other.heading), requests(other.requests) {}
    
    Elevator& operator=(const Elevator& other) {
        if (this != &other) {
            doorDelay = other.doorDelay;
            moveDelay = other.moveDelay;
            current = other.current;
            state = other.state;
            doorState = other.doorState;
            heading = other.heading;
            requests = other.requests;
        }
        return *this;
    }

    Elevator(Elevator&& other) noexcept
            : doorDelay(other.doorDelay), moveDelay(other.moveDelay), current(other.current), state(other.state), doorState(other.doorState), heading(other.heading), requests(other.requests) {}

    Elevator& operator=(Elevator&& other) noexcept {
        if (this != &other) {
            doorDelay = other.doorDelay;
            moveDelay = other.moveDelay;
            current = other.current;
            state = other.state;
            doorState = other.doorState;
            heading = other.heading;
            requests = other.requests;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Elevator& elevator);

    bool IsIdle() override { return state == IDLE; }
    int CurrentFloor() override { return current; }

    std::unordered_set<int> RequestFloor(const int& floor) override {
        if(current == floor) {
            return requests;
        }
        auto search = requests.find(floor);
        if(search != requests.end()) {
            return requests;
        } 
        requests.insert(floor);
        Move();
        return requests;
    }
    protected:
    void Move() override {
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