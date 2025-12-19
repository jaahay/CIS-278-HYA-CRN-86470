#include "Passenger.h"
const int Passenger::Origin() const {
    return origin;
}
const int Passenger::Destination() const {
    return destination;
}

const bool Passenger::GoingMyWay(const Heading& heading) const {
    if (origin > destination) {
        return heading == GOING_DOWN;
    }
    if (origin < destination) {
        return heading == GOING_UP;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Passenger& passenger) {
    os << passenger.origin << "->" << passenger.destination;
    return os;
};

Passenger::Passenger(int origin = 1, int destination = 1)
    : origin(origin), destination(destination) {
    if (origin == destination) {
        throw std::invalid_argument("Embark and disembark from two different floors, please.");
    }
}