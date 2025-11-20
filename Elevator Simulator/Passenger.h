#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>

class IPassenger {
    public:
    virtual std::ostream& operator<<(std::ostream& os) const = 0;
 };

 #endif // PASSENGER_H