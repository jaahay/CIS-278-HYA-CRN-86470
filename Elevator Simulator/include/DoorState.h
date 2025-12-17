#ifndef DOORSTATE_H
#define DOORSTATE_H
#include <ostream>

class DoorState {
public:
    auto operator<=>(const DoorState&) const = default;
    bool operator==(const DoorState&) const = default;
    virtual std::ostream& operator<<(std::ostream& os) const = 0;
    friend std::ostream& operator<<(std::ostream&, const DoorState&);
};
class DoorsOpening : public DoorState {
    virtual std::ostream& operator<<(std::ostream& os) const;
};
const extern DoorsOpening DOORS_OPENING;
class DoorsOpen : public DoorState {
    virtual std::ostream& operator<<(std::ostream& os) const;
};
const extern DoorsOpen DOORS_OPEN;
class DoorsClosing : public DoorState {
    virtual std::ostream& operator<<(std::ostream& os) const;
};
const extern DoorsClosing DOORS_CLOSING;
class DoorsClosed : public DoorState {
    virtual std::ostream& operator<<(std::ostream& os) const;
};
const extern DoorsClosed DOORS_CLOSED;

#endif // DOORSTATE_H