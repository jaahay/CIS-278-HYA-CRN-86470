#include "ActiveState.h"
std::ostream& operator<<(std::ostream& os, const ActiveState& state) {
    return state << os;
}
std::ostream& Idle::operator<<(std::ostream& os) const {
    return os << "Elevator is idle.";
}
const extern Idle IDLE = Idle();
std::ostream& Active::operator<<(std::ostream& os) const {
    return os << "Elevator is active.";
}
const extern Active ACTIVE = Active();