#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>

class IHeading {
public: 
    bool operator==(const IHeading& other) const { return this == &other; };
    virtual std::ostream& Printout(std::ostream&) const = 0;
};

class IPassenger {
    public:
    virtual const int Origin() const = 0;
    virtual const int Destination() const = 0;
    virtual const IHeading* Heading() const = 0;
    virtual const IHeading* Direction(const int floor) const = 0;
 };

 #endif // PASSENGER_H