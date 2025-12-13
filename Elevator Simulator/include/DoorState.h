#ifndef DOORSTATE_H
#define DOORSTATE_H
#include <ostream>

class DoorState {
public:
    auto operator<=>(const DoorState&) const = default;
};
extern DoorState* DOORS_OPENING;
extern DoorState* DOORS_OPEN;
extern DoorState* DOORS_CLOSING;
extern DoorState* DOORS_CLOSED;

#endif // DOORSTATE_H