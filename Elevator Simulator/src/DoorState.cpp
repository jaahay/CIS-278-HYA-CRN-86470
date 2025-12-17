#include "DoorState.h"
std::ostream& operator<<(std::ostream& os, const DoorState& state) {
    return state << os;
}
std::ostream& DoorsOpening::operator<<(std::ostream& os) const {
    return os << "Doors are opening.";
};
const extern DoorsOpening DOORS_OPENING = DoorsOpening();
std::ostream& DoorsOpen::operator<<(std::ostream& os) const {
    return os << "Doors are open.";
};
const extern DoorsOpen DOORS_OPEN = DoorsOpen();
std::ostream& DoorsClosing::operator<<(std::ostream& os) const {
    return os << "Doors are closing.";
};
const extern DoorsClosing DOORS_CLOSING = DoorsClosing();
std::ostream& DoorsClosed::operator<<(std::ostream& os) const {
    return os << "Doors are closed.";
};
const extern DoorsClosed DOORS_CLOSED = DoorsClosed();