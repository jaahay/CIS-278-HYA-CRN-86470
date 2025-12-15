#include "ActiveState.h"

class Idle : public ActiveState {
};
extern std::ostream& operator<<(std::ostream& os, const Idle &) {
    os << "Elevator is idle.";
    return os;
}
ActiveState* IDLE = new Idle();

class Active : public ActiveState {
public:
};
extern std::ostream& operator<<(std::ostream &os, const Active &) {
    os << "Elevator is active.";
    return os;
}
ActiveState* ACTIVE = new Active();
