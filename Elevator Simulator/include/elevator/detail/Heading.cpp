#include "Heading.h"
template<typename Friend>
std::ostream& operator<<(std::ostream& os, const Heading<Friend>& heading) {
    return heading << os;
}
std::ostream& GoingUp::operator<<(std::ostream& os) const {
    return os << "Going up.";
};
extern const GoingUp GOING_UP = GoingUp::GOING_UP;
std::ostream& GoingDown::operator<<(std::ostream& os) const {
    os << "Going down.";
    return os;
};
extern const GoingDown GOING_DOWN = GoingDown::GOING_DOWN;
std::ostream& Stopped::operator<<(std::ostream& os) const {
    os << "Stopped.";
    return os;
};
extern const Stopped STOPPED = Stopped::STOPPED;