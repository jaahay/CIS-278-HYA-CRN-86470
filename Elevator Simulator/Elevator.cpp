#include <cstddef>
#include <cstring>

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

class Elevator : public IElevator {
        
    protected:
        int currentFloor{0};
        const State* statePtr{nullptr};
    public:
    Elevator() : currentFloor(0), statePtr(IDLE) {}
    int MoveToFloor(int floor) {
        currentFloor = floor;
        return currentFloor;
    }
    int Floor() {
        return currentFloor;
    }
    State* OpenDoors() {
        statePtr = DOORS_OPEN;
        return const_cast<State*>(statePtr);
    }
    State* CloseDoors() {
        statePtr = DOORS_CLOSED;
        return const_cast<State*>(statePtr);
    }
};