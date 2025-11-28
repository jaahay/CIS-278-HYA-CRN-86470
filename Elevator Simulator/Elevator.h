#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <algorithm>
#include <iostream>
#include <list>

#include "Passenger.h"

class State {
public: 
    bool operator==(const State& other) const { return this == &other; };
    virtual std::ostream& print(std::ostream&) const = 0;
};

class Idle : public State {
public:
    std::ostream& print(std::ostream& os) const override {
        os << "Elevator is idle.";
        return os;
    }
};
class Active : public State {
public:
    std::ostream& print(std::ostream& os) const override {
        os << "Elevator is active.";
        return os;
    }
};
static const State* IDLE = new Idle();
static const State* ACTIVE = new Active();

class DoorState {
public: 
    bool operator==(const DoorState& other) const { return this == &other; };
    virtual std::ostream& print(std::ostream&) const = 0;
};
class DoorsOpening : public DoorState {
public:
    std::ostream& print(std::ostream& os) const override {
        os << "Doors are opening.";
        return os;
    }
};
class DoorsOpen : public DoorState {
public:
    std::ostream& print(std::ostream& os) const override {
        os << "Doors are open.";
        return os;
    }
};
class DoorsClosing : public DoorState {
public:
    std::ostream& print(std::ostream& os) const override {
        os << "Doors are closing.";
        return os;
    }
};
class DoorsClosed : public DoorState {
public:
    std::ostream& print(std::ostream& os) const override {
        os << "Doors are closed.";
        return os;
    }
};

static const DoorState* DOORS_OPENING = new DoorsOpening();
static const DoorState* DOORS_OPEN = new DoorsOpen();
static const DoorState* DOORS_CLOSING = new DoorsClosing();
static const DoorState* DOORS_CLOSED = new DoorsClosed();
    
class IElevator {
    public:
    virtual const bool IsIdle() const = 0;
    virtual const int CurrentFloor() const = 0;
    virtual const std::list<const IPassenger *> ReceivePassenger(const IPassenger &) = 0;

    /**
     * Calculate how inconvenient it would be to pick up a passenger. Cases:
     * 1. Same floor, doors opened and either stopped or same direction (0-distance)
     * 2. Stopped; no direction (distance between current floor and passenger's origin)
     * 3. Heading in same direction and away floor (twice distance between current and farthest + distance between current and passenger's origin)
     * 4. Heading in same direction on approach floor (distance between current and passenger's origin)
     * 5. Heading in opposite direction ( distance between farthest and current + distance between farthest and passenger's origin)
     */
    virtual const double Divergence(const IPassenger &) const = 0;
    virtual const std::ostream& print(std::ostream&) const = 0;
};

const std::ostream& operator<<(std::ostream& os, const IElevator& elevator) { return elevator.print(os); }

#endif // ELEVATOR_H
