#include <chrono>
#include <cstddef>
#include <cstring>
#include <future>
#include <iostream>
#include <thread>

#include "Elevator.h"

class DoorsOpen : public IState {
public:
    void toString(char* buffer, size_t bufferSize) const override {
        strncpy(buffer, "Doors are open", bufferSize);
        if (bufferSize > 0) buffer[bufferSize - 1] = '\0';
    }
};

class DoorsClosed : public IState {
public:
    void toString(char* buffer, size_t bufferSize) const override {
        strncpy(buffer, "Doors are closed", bufferSize);
        if (bufferSize > 0) buffer[bufferSize - 1] = '\0';
    }
};

class Active : public IState {
public:
    void toString(char* buffer, size_t bufferSize) const override {
        strncpy(buffer, "Elevator is active", bufferSize);
        if (bufferSize > 0) buffer[bufferSize - 1] = '\0';
    }
};

class Idle : public IState {
public:
    void toString(char* buffer, size_t bufferSize) const override {
        strncpy(buffer, "Elevator is idle", bufferSize);
        if (bufferSize > 0) buffer[bufferSize - 1] = '\0';
    }
};

static const IState* DOORS_OPEN = new DoorsOpen();
static const IState* DOORS_CLOSED = new DoorsClosed();
static const IState* ACTIVE = new Active();
static const IState* IDLE = new Idle();

class Elevator : public IElevator {
    private:
    static const int DOOR_DELAY_MS = 300;
    static const int MOVE_DELAY_MS = 500;

    private:
        int doorDelayMs;
        int moveDelayMs;
        int currentFloor;
        int destinationFloor;
        IState* statePtr;

    public:
    Elevator(int initialFloor = 1, int doorDelay = DOOR_DELAY_MS, int moveDelay = MOVE_DELAY_MS)
        : currentFloor(initialFloor), doorDelayMs(doorDelay), moveDelayMs(moveDelay), statePtr((IState*)IDLE), destinationFloor(initialFloor) {}
    
    ~Elevator() {}
    Elevator(const Elevator& other) : currentFloor(other.currentFloor), doorDelayMs(other.doorDelayMs), moveDelayMs(other.moveDelayMs), statePtr(other.statePtr), destinationFloor(other.destinationFloor) {}
    Elevator& operator=(const Elevator& other) {
        if (this != &other) {
            currentFloor = other.currentFloor;
            doorDelayMs = other.doorDelayMs;
            moveDelayMs = other.moveDelayMs;
            statePtr = other.statePtr;
            destinationFloor = other.destinationFloor;
        }
        return *this;
    }
    Elevator(Elevator&& other) noexcept
        : currentFloor(other.currentFloor), doorDelayMs(other.doorDelayMs), moveDelayMs(other.moveDelayMs), statePtr(other.statePtr), destinationFloor(other.destinationFloor) {}
    Elevator& operator=(Elevator&& other) noexcept {
        if (this != &other) {
            currentFloor = other.currentFloor;
            doorDelayMs = other.doorDelayMs;
            moveDelayMs = other.moveDelayMs;
            statePtr = other.statePtr;
            destinationFloor = other.destinationFloor;
        }
        return *this;
    }

    int GetCurrentFloor() const override {
        return currentFloor;
    }

    void MoveToFloor(int floor) override {
        if( floor < 1 ) {
            throw std::invalid_argument("Floor number must be positive.");
        }
        if( statePtr == (IState*)ACTIVE || statePtr == (IState*)DOORS_CLOSED || statePtr == (IState*)DOORS_OPEN ) {
            throw std::logic_error("Elevator is already moving.");
        }
        if ( floor == currentFloor ) {
            std::cout << "Elevator is already at floor " << floor << "." << std::endl;
            return;
        }
        std::cout << "Moving elevator from floor " << currentFloor << " to floor " << floor << "..." << std::endl;
        statePtr = (IState*)ACTIVE;
        destinationFloor = floor;
        std::thread t([this, floor]() {
            statePtr = (IState*)DOORS_CLOSED;
            std::this_thread::sleep_for(std::chrono::milliseconds(doorDelayMs)); // Simulate door closing time
            statePtr = (IState*)ACTIVE;
            while(currentFloor != floor) {
                if (currentFloor < floor) {
                    currentFloor++;
                } else {
                    currentFloor--;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(moveDelayMs)); // Simulate time taken to move one floor
            }
            statePtr = (IState*)DOORS_OPEN;
            std::this_thread::sleep_for(std::chrono::milliseconds(doorDelayMs)); // Simulate door opening time
            statePtr = (IState*)IDLE;
            std::cout << "Elevator has arrived at floor " << currentFloor << "." << std::endl;
            return currentFloor;
        });
        t.detach();
    }
    bool IsIdle() const override {
        return statePtr == IDLE;
    }

    void toString(char* buffer, size_t bufferSize) const override {
        snprintf(buffer, bufferSize, "Elevator is currently at floor %d last sent to floor %d. State: ", currentFloor, destinationFloor);
        size_t len = strlen(buffer);
        statePtr->toString(buffer + len, bufferSize - len);
    }
};

std::ostream& operator<<(std::ostream& os, const IState& state) {
    char buffer[1024];
    state.toString(buffer, sizeof(buffer));
    os << buffer;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Elevator& elevator) {
    char buffer[1024];
    elevator.toString(buffer, sizeof(buffer));
    os << buffer;
    return os;
}