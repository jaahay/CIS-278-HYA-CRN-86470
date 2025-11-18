#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <cstring>
#include <future>

class State {
    public:
    static const State DOORS_OPEN;
    static const State DOORS_CLOSED;
    static const State ACTIVE;
    static const State IDLE;

    void toString(char* buffer, size_t bufferSize) const {
        strncpy(buffer, "Base State", bufferSize);
        if (bufferSize > 0) buffer[bufferSize - 1] = '\0';
    }
};

class Elevator {
    public:
    virtual int GetCurrentFloor() = 0;
    virtual std::future<int> MoveToFloor(int floor) = 0;
    virtual bool IsIdle() = 0;
};

#endif // ELEVATOR_H
