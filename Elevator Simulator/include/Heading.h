#ifndef HEADING_H
#define HEADING_H
#include <ostream>

class Heading {
public:
    auto operator<=>(const Heading&) const = default;
};
extern Heading* GOING_UP;
extern Heading* GOING_DOWN;
extern Heading* STOPPED;

#endif // !HEADING_H