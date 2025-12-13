#include "DoorState.h"

class DoorsOpening : public DoorState {
};
extern std::ostream& operator<<(std::ostream& os, const DoorsOpening&) {
    os << "Doors are opening.";
    return os;
};
class DoorsOpen : public DoorState {
};
extern std::ostream& operator<<(std::ostream& os, const DoorsOpen&) {
    os << "Doors are open.";
    return os;
};
class DoorsClosing : public DoorState {
};
extern std::ostream& operator<<(std::ostream& os, const DoorsClosing&) {
    os << "Doors are closing.";
    return os;
};
class DoorsClosed : public DoorState {};
extern std::ostream& operator<<(std::ostream& os, const DoorsClosed&) {
    os << "Doors are closed.";
    return os;
};
DoorState* DOORS_OPENING = new DoorsOpening();
DoorState* DOORS_OPEN = new DoorsOpen();
DoorState* DOORS_CLOSING = new DoorsClosing();
DoorState* DOORS_CLOSED = new DoorsClosed();