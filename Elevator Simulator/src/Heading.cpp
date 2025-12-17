#include "Heading.h"
std::ostream& operator<<(std::ostream& os, const Heading& heading) {
    return heading << os;
}
std::ostream& GoingUp::operator<<(std::ostream& os) const {
    return os << "Going up.";
};
const extern GoingUp GOING_UP = GoingUp();
std::ostream& GoingDown::operator<<(std::ostream& os) const {
    os << "Going down.";
    return os;
};
const extern GoingDown GOING_DOWN = GoingDown();
std::ostream& Stopped::operator<<(std::ostream& os) const {
    os << "Stopped.";
    return os;
};
const extern Stopped STOPPED = Stopped();