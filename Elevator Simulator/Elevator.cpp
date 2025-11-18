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
    private:
    static const int DOOR_DELAY_MS = 300;
    static const int MOVE_DELAY_MS = 500;

    private:
        int doorDelayMs;
        int moveDelayMs;
        int currentFloor;
        State* statePtr;

    public:
    ElevatorImpl(int doorDelay = DOOR_DELAY_MS, int moveDelay = MOVE_DELAY_MS) : doorDelayMs(doorDelay), moveDelayMs(moveDelay), currentFloor(1), statePtr((State*)IDLE) {}
    ElevatorImpl(const ElevatorImpl& other) : currentFloor(other.currentFloor), statePtr((State*)IDLE) {}
    
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

    int GetCurrentFloor() {
        return currentFloor;
    }

    int MoveToFloor(int floor) {
        if( floor < 1 ) {
            throw std::invalid_argument("Floor number must be positive.");
        }
        if( statePtr == ACTIVE ) {
            throw std::logic_error("Elevator is already moving.");
        }
        if( floor == currentFloor ) {
            return currentFloor;
        }
        statePtr = (State*)DOORS_CLOSED;
        std::this_thread::sleep_for(std::chrono::milliseconds(doorDelayMs)); // Simulate door closing time
        statePtr = (State*)ACTIVE;
        while(currentFloor != floor) {
            if (currentFloor < floor) {
                currentFloor++;
            } else {
                currentFloor--;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(moveDelayMs));
        }
        statePtr = (State*)DOORS_OPEN;
        std::this_thread::sleep_for(std::chrono::milliseconds(doorDelayMs)); // Simulate door opening time
        statePtr = (State*)IDLE;
        return currentFloor;
    }
    bool IsIdle() {
        return statePtr == IDLE;
    }
    void toString(char* buffer, size_t bufferSize) const {
        if (statePtr) {
            statePtr->toString(buffer, bufferSize);
        } else {
            strncpy(buffer, "Unknown state", bufferSize);
            if (bufferSize > 0) buffer[bufferSize - 1] = '\0';
        }
    }   
};