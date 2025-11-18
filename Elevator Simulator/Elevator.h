#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <cstring>

class State {
    public:
    static const State DOORS_OPEN;
    static const State DOORS_CLOSED;
    static const State ACTIVE;
    static const State IDLE;
};

class Elevator {
    public:
        virtual int MoveToFloor(int floor) = 0;
        virtual bool IsIdle() = 0;
};

#endif // ELEVATOR_H
