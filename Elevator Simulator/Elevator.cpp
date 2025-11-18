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
        IState* statePtr;

    public:
    Elevator(int doorDelay = DOOR_DELAY_MS, int moveDelay = MOVE_DELAY_MS) : doorDelayMs(doorDelay), moveDelayMs(moveDelay), currentFloor(1), statePtr((IState*)IDLE) {}
    Elevator(const Elevator& other) : currentFloor(other.currentFloor), statePtr((IState*)IDLE) {}
    
    ~Elevator() {}
    
    Elevator& operator=(const Elevator& other) {
        if (this != &other) {
            currentFloor = other.currentFloor;
            statePtr = other.statePtr;
        }
        return *this;
    }

    Elevator(const Elevator&& other) noexcept {
        currentFloor = other.currentFloor;
        statePtr = other.statePtr;
    }

    Elevator& operator=(const Elevator&& other) noexcept {
        if (this != &other) {
            currentFloor = other.currentFloor;
            statePtr = other.statePtr;
        }
        return *this;
    }

    int GetCurrentFloor() const override {
        return currentFloor;
    }

    std::future<int> MoveToFloor(int floor) override {
        if( floor < 1 ) {
            throw std::invalid_argument("Floor number must be positive.");
        }
        if( statePtr == (IState*)ACTIVE || statePtr == (IState*)DOORS_CLOSED || statePtr == (IState*)DOORS_OPEN ) {
            throw std::logic_error("Elevator is already moving.");
        }
        if( floor == currentFloor ) {
            return std::async(std::launch::async, [this]() {
                return this->currentFloor;
            });
        }
        statePtr = (IState*)DOORS_CLOSED;
        std::this_thread::sleep_for(std::chrono::milliseconds(doorDelayMs)); // Simulate door closing time
        return std::async(std::launch::async, [this, floor]() {
            std::cout << "Moving elevator from floor " << currentFloor << " to floor " << floor << "..." << std::endl;
            statePtr = (IState*) ACTIVE;
            while(currentFloor != floor) {
                if (currentFloor < floor) {
                    currentFloor++;
                } else {
                    currentFloor--;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(moveDelayMs)); // Simulate time taken to move one floor
                std::cout << "Elevator arrived at floor " << currentFloor << "." << std::endl;
            }
            statePtr = (IState*)DOORS_OPEN;
            std::this_thread::sleep_for(std::chrono::milliseconds(doorDelayMs)); // Simulate door opening time
            statePtr = (IState*)IDLE;
            std::cout << "Elevator has arrived at floor " << currentFloor << "." << std::endl;
            return currentFloor;
        });
    }
    bool IsIdle() const override {
        return statePtr == IDLE;
    }

    void toString(char* buffer, size_t bufferSize) const override {
        strncpy(buffer, "Elevator status:", bufferSize);
        if (bufferSize > 0) buffer[bufferSize - 1] = '\0';
        char stateBuffer[50];
        statePtr->toString(stateBuffer, sizeof(stateBuffer));
        strncat(buffer, " ", bufferSize - strlen(buffer) - 1);
        strncat(buffer, stateBuffer, bufferSize - strlen(buffer) - 1);
    }
};