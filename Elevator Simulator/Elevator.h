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

class DoorState {
public: 
    bool operator==(const DoorState& other) const { return this == &other; };
    virtual std::ostream& Printout(std::ostream&) const = 0;
};
    
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

static bool Within(const int floor, const IPassenger& passenger) {
    const auto [lower, higher] = std::minmax(passenger.Origin(), passenger.Destination());
    return lower <= floor && floor <= higher;
}

#endif // ELEVATOR_H
