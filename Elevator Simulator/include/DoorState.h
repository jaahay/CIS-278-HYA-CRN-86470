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
public:
    static const DoorsOpening DOORS_OPENING;
private:
    DoorsOpening() = default;
};
extern const DoorsOpening DOORS_OPENING;
class DoorsOpen : public DoorState {
    virtual std::ostream& operator<<(std::ostream& os) const;
public:
    static const DoorsOpen DOORS_OPEN;
private:
    DoorsOpen() = default;
};
extern const DoorsOpen DOORS_OPEN;
class DoorsClosing : public DoorState {
    virtual std::ostream& operator<<(std::ostream& os) const;
public:
    static const DoorsClosing DOORS_CLOSING;
private:
    DoorsClosing() = default;
};
extern const DoorsClosing DOORS_CLOSING;
class DoorsClosed : public DoorState {
    virtual std::ostream& operator<<(std::ostream& os) const;
public:
    static const DoorsClosed DOORS_CLOSED;
private:
    DoorsClosed() = default;
};
extern const DoorsClosed DOORS_CLOSED;

#endif // DOORSTATE_H