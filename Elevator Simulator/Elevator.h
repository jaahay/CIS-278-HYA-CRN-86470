#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include <unordered_set>

class State {};

class DoorState {};

class Heading {};

class IElevator {
    public:
    virtual int CurrentFloor() = 0;
    virtual bool IsIdle() = 0;
    virtual std::unordered_set<int> RequestFloor(const int floor) = 0;
    
    protected:
    virtual void Move() = 0;
};

#endif // ELEVATOR_H
