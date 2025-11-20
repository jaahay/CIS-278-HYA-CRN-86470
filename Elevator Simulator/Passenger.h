#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>

#include "Panel.h"

class IPosition {
    public:
    virtual std::ostream& operator<<(std::ostream& os) const = 0;
};

template <typename T>
class IPassenger {
    public:
    virtual std::ostream& operator<<(std::ostream& os) const = 0;

    virtual T* origin() const = 0;
    virtual T* destination() const = 0;
 };

 #endif // PASSENGER_H