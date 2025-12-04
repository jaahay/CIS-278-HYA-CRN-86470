#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>

class IHeading {
public: 
    auto operator<=>(const IHeading &) const = default;
    virtual std::ostream& print(std::ostream&) const = 0;
};

class GoingUp : public IHeading {
public:
    std::ostream& print(std::ostream& os) const override {
        os << "Going up.";
        return os;
    }
};
class GoingDown : public IHeading {
public:
    std::ostream& print(std::ostream& os) const override {
        os << "Going down.";
        return os;
    }
};
class Stopped : public IHeading {
public:
    std::ostream& print(std::ostream& os) const override {
        os << "Stopped.";
        return os;
    }
};
static const IHeading* GOING_UP = new GoingUp();
static const IHeading* GOING_DOWN = new GoingDown();
static const IHeading* STOPPED = new Stopped();

class IPassenger {
    public:
    virtual const int Origin() const = 0;
    virtual const int Destination() const = 0;
    virtual const IHeading* Heading() const = 0;
    virtual const std::ostream& print(std::ostream&) const = 0;

    auto operator<=>(const IPassenger &) const = default;
 };

 #endif // PASSENGER_H