#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <cstring>
#include <future>

class IState {
    public:
    static const IState DOORS_OPEN;
    static const IState DOORS_CLOSED;
    static const IState ACTIVE;
    static const IState IDLE;

    virtual void toString(char* buffer, size_t bufferSize) const = 0;
};

class IElevator {
    public:
    virtual int GetCurrentFloor() const = 0;
    virtual void MoveToFloor(int floor) = 0;
    virtual bool IsIdle() const = 0;
    
    virtual void toString(char* buffer, size_t bufferSize) const = 0;
};

#endif // ELEVATOR_H
