#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>

class IHeading {
public: 
    bool operator==(const IHeading& other) const { return this == &other; };
    virtual std::ostream& Printout(std::ostream&) const = 0;
};

class GoingUp : public IHeading {
public:
    std::ostream& Printout(std::ostream& os) const override {
        os << "Going up.";
        return os;
    }
};
class GoingDown : public IHeading {
public:
    std::ostream& Printout(std::ostream& os) const override {
        os << "Going down.";
        return os;
    }
};
class Stopped : public IHeading {
public:
    std::ostream& Printout(std::ostream& os) const override {
        os << "Stopped.";
        return os;
    }
};
static const GoingUp* GOING_UP = new GoingUp();
static const GoingDown* GOING_DOWN = new GoingDown();
static const Stopped* STOPPED = new Stopped();

class IPassenger {
    public:
    virtual const int Origin() const = 0;
    virtual const int Destination() const = 0;
    virtual const IHeading* Heading() const = 0;
    virtual const IHeading* Direction(const int floor) const = 0;
 };

 #endif // PASSENGER_H