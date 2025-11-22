#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>

class IPassenger {
    public:
    virtual int Origin() = 0;
    virtual int Destination() = 0;
 };

 #endif // PASSENGER_H