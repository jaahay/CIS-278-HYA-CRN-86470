#include "Passenger.h"

#include <stdexcept>

class Passenger : public IPassenger {
    private:
    const int origin;
    const int destination;

    public:

    Passenger(int origin = 1, int destination = 1)
        : origin(origin), destination(destination) {
            if(origin == destination) {
                throw std::invalid_argument("Embark and disembark from two different floors, please.");
            }
        }

    // ~Passenger() {}

    // Passenger(const Passenger& other)
    //     : origin(other.origin), destination(other.destination) {}

    // Passenger& operator=(const Passenger& other) {
    //     if (this != &other) {
    //         origin = other.origin;
    //         destination = other.destination;
    //     }
    //     return *this;
    // }

    // Passenger(Passenger&& other) noexcept
    //     : origin(other.origin), destination(other.destination) {}

    // Passenger& operator=(Passenger&& other) noexcept {
    //     if (this != &other) {
    //         origin = other.origin;
    //         destination = other.destination;
    //     }
    //     return *this;
    // }
    
    friend std::ostream& operator<<(std::ostream&, const Passenger&);

    const int Origin() const override { return origin; }
    const int Destination() const override { return destination; }

    const IHeading* Heading() const override {
        if(origin > destination) {
            return GOING_DOWN;
        }
        return GOING_UP;
    }
    const bool FloorWithin(const int floor) const override {
        if(floor >= origin) { return GOING_UP; }
        return GOING_DOWN;
    }
    
};

std::ostream& operator<<(std::ostream& os, const Passenger& passenger) {
    os << "Origin: " << passenger.origin;
    os << "Destination: " << passenger.destination;
    return os;
}