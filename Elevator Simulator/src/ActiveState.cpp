#include "ActiveState.h"
std::ostream& operator<<(std::ostream& os, const ActiveState& state) {
    return state << os;
}
std::ostream& Idle::operator<<(std::ostream& os) const {
    return os << "Elevator is idle.";
}
extern const Idle IDLE = Idle::IDLE;
std::ostream& Active::operator<<(std::ostream& os) const {
    return os << "Elevator is active.";
}
extern const Active ACTIVE = Active::ACTIVE;