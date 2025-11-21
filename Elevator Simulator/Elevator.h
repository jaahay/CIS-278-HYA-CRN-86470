#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include <unordered_set>

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

class Heading {
public: 
    bool operator==(const Heading& other) const { return this == &other; };
    virtual std::ostream& Printout(std::ostream&) const = 0;
};

class IElevator {
    public:
    virtual bool IsIdle() = 0;
    virtual int CurrentFloor() = 0;
    virtual std::unordered_set<int> RequestFloor(const int&) = 0;
    
    protected:
    virtual void Move() = 0;
};

#endif // ELEVATOR_H
