#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include "Heading.h"

class Passenger {
private:
    int origin;
    int destination;
public:
    const int Origin() const {
        return origin;
    }
    const int Destination() const {
        return destination;
    }
    const Heading* Heading() const {
        if (origin > destination) {
            return GOING_DOWN;
        }
        return GOING_UP;
    };

    friend std::ostream& operator<<(std::ostream& os, const Passenger& passenger) {
        os << passenger.origin << "->" << passenger.destination;
        return os;
    };

    Passenger(int origin = 1, int destination = 1)
        : origin(origin), destination(destination) {
        if (origin == destination) {
            throw std::invalid_argument("Embark and disembark from two different floors, please.");
        }
    }
    ~Passenger() = default;
    Passenger(const Passenger& other) :
        origin(other.origin), destination(other.destination) {
    }
    Passenger& operator=(const Passenger&) = delete;
    Passenger(Passenger&& other) noexcept :
        origin(other.origin), destination(other.destination) {
    }
    Passenger& operator=(Passenger&&) = delete;
    auto operator<=>(const Passenger &) const = default;
 };
 #endif // PASSENGER_H