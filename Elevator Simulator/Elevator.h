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

class IElevator {
    public:
        virtual int Floor() = 0;
        virtual int MoveToFloor(int floor) = 0;
        virtual State* OpenDoors() = 0;
        virtual State* CloseDoors() = 0;
};

#endif // ELEVATOR_H