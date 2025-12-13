#include "Heading.h"

class GoingUp : public Heading {
};
extern std::ostream& operator<<(std::ostream& os, const GoingUp&) {
    os << "Going up.";
    return os;
};
class GoingDown : public Heading {
};
extern std::ostream& operator<<(std::ostream& os, const GoingDown&) {
    os << "Going down.";
    return os;
};
class Stopped : public Heading {
};
extern std::ostream& operator<<(std::ostream& os, const Stopped&) {
    os << "Stopped.";
    return os;
};
Heading* GOING_UP = new GoingUp();
Heading* GOING_DOWN = new GoingDown();
Heading* STOPPED = new Stopped();