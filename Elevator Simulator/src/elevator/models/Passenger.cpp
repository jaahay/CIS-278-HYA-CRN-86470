#include "elevator/Passenger.h"
#include "elevator/DomainStates.h"

using elevator::detail::Heading;
using elevator::DomainStates::GoingUp;
using elevator::DomainStates::GoingDown;

constexpr int Passenger::Origin() const {
    return origin;
}
constexpr int Passenger::Destination() const {
    return destination;
}
const bool Passenger::GoingMyWay(const Heading* heading) const {
    if (heading == &GoingUp() && destination > origin) { return true; }
    if (heading == &GoingDown() && destination < origin) { return true; }
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