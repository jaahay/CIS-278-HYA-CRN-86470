#include <stdexcept>

#include "../include/Passenger.h"

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

    ~Passenger() {}

    Passenger(const Passenger& other) :
        origin(other.origin), destination(other.destination) {}

    Passenger& operator=(const Passenger&) = delete;

    Passenger(Passenger&& other) noexcept :
        origin(other.origin), destination(other.destination) {}

    Passenger& operator=(Passenger&&) = delete;

    const int Origin() const override { return origin; }
    const int Destination() const override { return destination; }

    const IHeading* Heading() const override {
        if(origin > destination) {
            return GOING_DOWN;
        }
        return GOING_UP;
    }

    const std::ostream& print(std::ostream& os) const override {
        os << origin << "->" << destination;
        return os;
    }
};