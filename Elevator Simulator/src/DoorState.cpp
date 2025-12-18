#include "DoorState.h"
std::ostream& operator<<(std::ostream& os, const DoorState& state) {
    return state << os;
}
std::ostream& DoorsOpening::operator<<(std::ostream& os) const {
    return os << "Doors are opening.";
};
extern const DoorsOpening DOORS_OPENING = DoorsOpening::DOORS_OPENING;
std::ostream& DoorsOpen::operator<<(std::ostream& os) const {
    return os << "Doors are open.";
};
extern const DoorsOpen DOORS_OPEN = DoorsOpen::DOORS_OPEN;
std::ostream& DoorsClosing::operator<<(std::ostream& os) const {
    return os << "Doors are closing.";
};
extern const DoorsClosing DOORS_CLOSING = DoorsClosing::DOORS_CLOSING;
std::ostream& DoorsClosed::operator<<(std::ostream& os) const {
    return os << "Doors are closed.";
};
extern const DoorsClosed DOORS_CLOSED = DoorsClosed::DOORS_CLOSED;