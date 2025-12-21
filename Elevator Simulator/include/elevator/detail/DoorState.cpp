#include "DoorState.h"
// Friend-ly Door State Insertion Definition
std::ostream& operator<<(std::ostream& os, const DoorState& state) {
    return state << os;
}
extern const DoorsOpen DOORS_OPEN = DoorsOpen::DOORS_OPEN;
extern const std::shared_ptr<const DoorsOpen> DOORS_OPEN_PTR = std::make_shared<const DoorsOpen>(DOORS_OPEN);
std::ostream& DoorsOpen::operator<<(std::ostream& os) const {
    return os << "Doors are open.";
};
extern const DoorsClosed DOORS_CLOSED = DoorsClosed::DOORS_CLOSED;
extern const std::shared_ptr<const DoorsClosed> DOORS_CLOSED_PTR = std::make_shared<const DoorsClosed>(DOORS_CLOSED);
std::ostream& DoorsClosed::operator<<(std::ostream& os) const {
    return os << "Doors are closed.";
};
extern const DoorsOpening DOORS_OPENING = DoorsOpening::DOORS_OPENING;
extern const std::shared_ptr<const 
std::ostream& DoorsOpening::operator<<(std::ostream& os) const {
    return os << "Doors are opening.";
};
extern const DoorsClosing DOORS_CLOSING = DoorsClosing::DOORS_CLOSING;
std::ostream& DoorsClosing::operator<<(std::ostream& os) const {
    return os << "Doors are closing.";
};