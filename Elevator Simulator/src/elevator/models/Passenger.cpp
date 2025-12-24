// elevator/models/Passenger.cpp
#include "elevator/models/Passenger.h"
#include "elevator/states/ElevatorStates.h"
#include <stdexcept>

using elevator::states::Heading;
using elevator::states::GoingUp;
using elevator::states::GoingDown;

constexpr int elevator::models::Passenger::Origin() const {
    return origin;
}

constexpr int elevator::models::Passenger::Destination() const {
    return destination;
}

bool elevator::models::Passenger::GoingMyWay(const Heading* heading) const {
    if (heading == &GoingUp() && destination > origin) {
        return true;
    }
    if (heading == &GoingDown() && destination < origin) {
        return true;
    }
    return false;
}

std::ostream& elevator::models::operator<<(std::ostream& os, const Passenger& passenger) {
    os << passenger.origin << "->" << passenger.destination;
    return os;
}

elevator::models::Passenger::Passenger(int origin, int destination)
    : origin(origin), destination(destination) {
    if (origin == destination) {
        throw std::invalid_argument("Embark and disembark from two different floors, please.");
    }
}
