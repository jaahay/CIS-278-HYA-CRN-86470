#include <chrono>
#include <cstddef>
#include <cstring>
#include <thread>

#include "Elevator.h"


class DoorsOpen : public State {
public:
    void toString(char* buffer, size_t bufferSize) const {
        strncpy(buffer, "Doors are open", bufferSize);
        if (bufferSize > 0) buffer[bufferSize - 1] = '\0';
    }
};

class DoorsClosed : public State {
public:
    void toString(char* buffer, size_t bufferSize) const {
        strncpy(buffer, "Doors are closed", bufferSize);
        if (bufferSize > 0) buffer[bufferSize - 1] = '\0';
    }
};

class Active : public State {
public:
    void toString(char* buffer, size_t bufferSize) const {
        strncpy(buffer, "Elevator is active", bufferSize);
        if (bufferSize > 0) buffer[bufferSize - 1] = '\0';
    }
};

class Idle : public State {
public:
    void toString(char* buffer, size_t bufferSize) const {
        strncpy(buffer, "Elevator is idle", bufferSize);
        if (bufferSize > 0) buffer[bufferSize - 1] = '\0';
    }
};

static const State* DOORS_OPEN = new DoorsOpen();
static const State* DOORS_CLOSED = new DoorsClosed();
static const State* ACTIVE = new Active();
static const State* IDLE = new Idle();

class ElevatorImpl : public Elevator {
    private: static const int MOVE_DELAY_MS = 500;

    private:
        int currentFloor{1};
        const State* statePtr{nullptr};

    public:
    ElevatorImpl() : currentFloor(1), statePtr(IDLE) {}
    ElevatorImpl(const ElevatorImpl& other) : currentFloor(other.currentFloor), statePtr(other.statePtr) {}
    
    ~ElevatorImpl() {}
    
    ElevatorImpl& operator=(const ElevatorImpl& other) {
        if (this != &other) {
            currentFloor = other.currentFloor;
            statePtr = other.statePtr;
        }
        return *this;
    }

    ElevatorImpl(const ElevatorImpl&& other) noexcept {
        currentFloor = other.currentFloor;
        statePtr = other.statePtr;
    }

    ElevatorImpl& operator=(const ElevatorImpl&& other) noexcept {
        if (this != &other) {
            currentFloor = other.currentFloor;
            statePtr = other.statePtr;
        }
        return *this;
    }

    int MoveToFloor(int floor) {
        if( floor < 1 ) {
            throw std::invalid_argument("Floor number must be positive.");
        }
        if( statePtr == ACTIVE ) {
            throw std::logic_error("Elevator is already moving.");
        }
        if( statePtr == DOORS_OPEN ) {
            throw std::logic_error("Cannot move elevator while doors are open.");
        }
        if( floor == currentFloor ) {
            return currentFloor;
        }
        statePtr = ACTIVE;
        while(currentFloor != floor) {
            if (currentFloor < floor) {
                currentFloor++;
            } else {
                currentFloor--;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(MOVE_DELAY_MS));
        }
        statePtr = IDLE;
        return currentFloor;
    }
    bool IsIdle() {
        return statePtr == IDLE;
    }
};