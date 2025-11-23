#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <algorithm>
#include <iostream>
#include <unordered_set>

#include "Passenger.h"

class State {
public: 
    bool operator==(const State& other) const { return this == &other; };
    virtual std::ostream& Printout(std::ostream&) const = 0;
};

class Idle : public State {
public:
    std::ostream& Printout(std::ostream& os) const override {
        os << "Elevator is idle.";
        return os;
    }
};
class Active : public State {
public:
    std::ostream& Printout(std::ostream& os) const override {
        os << "Elevator is moving.";
        return os;
    }
};
static const Idle* IDLE = new Idle();
static const Active* ACTIVE = new Active();

class DoorState {
public: 
    bool operator==(const DoorState& other) const { return this == &other; };
    virtual std::ostream& Printout(std::ostream&) const = 0;
};
class DoorsOpen : public DoorState {
public:
    std::ostream& Printout(std::ostream& os) const override {
        os << "Doors are open.";
        return os;
    }
};
class DoorsClosed : public DoorState {
public:
    std::ostream& Printout(std::ostream& os) const override {
        os << "Doors are closed.";
        return os;
    }
};
static const DoorsOpen* DOORS_OPEN = new DoorsOpen();
static const DoorsClosed* DOORS_CLOSED = new DoorsClosed();
    
class IElevator {
    public:
    virtual bool IsIdle() = 0;
    virtual int CurrentFloor() = 0;
    virtual double Divergence(const IPassenger&) const = 0;
    virtual std::unordered_set<IPassenger*> ReceivePassenger(const IPassenger&) = 0;
    virtual std::unordered_set<int> RequestFloor(const int&) = 0;
    
    protected:
    virtual void Move() = 0;
};

#endif // ELEVATOR_H
