#include "elevator/Passenger.h"
constexpr int Passenger::Origin() const {
    return origin;
}
constexpr int Passenger::Destination() const {
    return destination;
}
bool Passenger::GoingMyWay(const elevator::Heading& heading) const {
    if (heading == elevator::GOING_UP() && destination > origin) { return true; }
    if (heading == elevator::GOING_DOWN() && destination < origin) { return true; }
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