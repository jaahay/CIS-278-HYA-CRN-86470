#include <chrono>
#include <cstddef>
#include <cstring>
#include <future>
#include <iostream>
#include <unordered_set>
#include <thread>

#include "Elevator.h"
#include "Panel.h"
#include "Passenger.h"

class Active : public State {};
std::ostream& operator<<(std::ostream& os, const Active& _){
    os << "Elevator is moving.";
    return os;
};

class Idle : public State {};
std::ostream& operator<<(std::ostream& os, const Idle& _){
    os << "Elevator is idle.";
    return os;
};

static const State* ACTIVE = new Active();
static const State* IDLE = new Idle();

class DoorsOpen : public DoorState {};
std::ostream& operator<<(std::ostream& os, const DoorsOpen& _){
    os << "Doors are open.";
    return os;
};

class DoorsClosed : public DoorState {};
std::ostream& operator<<(std::ostream& os, const DoorsClosed& _){
    os << "Doors are closed.";
    return os;
};

static const DoorState* DOORS_OPEN = new DoorsOpen();
static const DoorState* DOORS_CLOSED = new DoorsClosed();

class GoingUp : public Heading {};
std::ostream& operator<<(std::ostream& os, const GoingUp& _){
    os << "Going up.";
    return os;
};

class GoingDown : public Heading {};
std::ostream& operator<<(std::ostream& os, const GoingDown& _){
    os << "Going down.";
    return os;
};

class Stopped : public Heading {};
std::ostream& operator<<(std::ostream& os, const Stopped& _){
    os << "Stopped.";
    return os;
};

static const Heading* GOING_UP = new GoingUp();
static const Heading* GOING_DOWN = new GoingDown();
static const Heading* STOPPED = new Stopped();

class Elevator : public IElevator {
    private:
    static const int DOOR_DELAY = 300;
    static const int MOVE_DELAY = 500;

    private:
        int doorDelay;
        int moveDelay;
        int current;
        State* state;
        Heading* heading;
        DoorState* doorState;
        std::unordered_set<int> requests;

    public:

    Elevator(int doorDelay = DOOR_DELAY, int moveDelay = MOVE_DELAY)
           : doorDelay(doorDelay), moveDelay(moveDelay), current(1), state((State*)IDLE), heading((Heading*)STOPPED), doorState((DoorState*)DOORS_OPEN), requests() {}
    
    ~Elevator() {}

    Elevator(const Elevator& other) : doorDelay(other.doorDelay), moveDelay(other.moveDelay), current(other.current), state(other.state), heading(other.heading), doorState(other.doorState), requests(other.requests) {}
    
    Elevator& operator=(const Elevator& other) {
        if (this != &other) {
            doorDelay = other.doorDelay;
            moveDelay = other.moveDelay;
            current = other.current;
            state = other.state;
            heading = other.heading;
            doorState = other.doorState;
            requests = other.requests;
        }
        return *this;
    }

    Elevator(Elevator&& other) noexcept
            : doorDelay(other.doorDelay), moveDelay(other.moveDelay), current(other.current), state(other.state), heading(other.heading), doorState(other.doorState), requests(other.requests) {}

    Elevator& operator=(Elevator&& other) noexcept {
        if (this != &other) {
            doorDelay = other.doorDelay;
            moveDelay = other.moveDelay;
            current = other.current;
            state = other.state;
            heading = other.heading;
            doorState = other.doorState;
            requests = other.requests;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Elevator& elevator);

    bool IsIdle() override { std::cout << state; return state == IDLE; }
    int CurrentFloor() override { return current; }

    std::unordered_set<int> RequestFloor(const int floor) override {
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
            state = (State*)ACTIVE;
            while(!requests.empty()) {
                if(requests.empty()) {
                    state = (State*)IDLE;
                    heading = (Heading*)STOPPED;
                    break;
                }
                auto search = requests.find(current);
                if(search != requests.end()) {
                    requests.erase(*search);
                    std::this_thread::sleep_for(std::chrono::milliseconds(doorDelay)); // Simulate door opening time
                    doorState = (DoorState*)DOORS_OPEN;
                }
                if(heading == STOPPED) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(doorDelay)); // Simulate door closing time
                    doorState = (DoorState*)DOORS_CLOSED;
                    int dest = *requests.begin();
                    int dist = dest - current;
                    for(const int& p : requests) {
                        if(std::abs(p - current) < dist) {
                            dest = p;
                            dist = p - current;
                        }
                    }
                    heading = (Heading*) ( dist > 0 ? GOING_UP : GOING_DOWN );
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
        });
        t.detach();
    }
};

std::ostream& operator<<(std::ostream& os, const Elevator& elevator) {
    os << "Elevator is currently at floor " << elevator.current << ".";
    os << " " << elevator.state << " " << elevator.heading << " " << elevator.doorState << "";
    return os;
}