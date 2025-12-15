#include "ActiveState.h"

class Idle : public ActiveState {
};
extern std::ostream& operator<<(std::ostream& os, const Idle &) {
    os << "Elevator is idle.";
    return os;
}
class Active : public ActiveState {
public:
};
extern std::ostream& operator<<(std::ostream &os, const Active &) {
    os << "Elevator is active.";
    return os;
}
ActiveState* IDLE = new Idle();
ActiveState* ACTIVE = new Active();
