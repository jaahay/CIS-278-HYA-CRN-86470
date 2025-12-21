#ifndef DOORSTATE_H
#define DOORSTATE_H
#include <ostream>
// Abstract Door State
class DoorState {
public:
    auto operator<=>(const DoorState&) const = default;
    bool operator==(const DoorState&) const = default;
    virtual std::ostream& operator<<(std::ostream& os) const = 0;
    friend std::ostream& operator<<(std::ostream&, const DoorState&);
};
// Doors Open Declaration
class DoorsOpen : public DoorState {
    virtual std::ostream& operator<<(std::ostream& os) const;
public:
    static const DoorsOpen DOORS_OPEN;
private:
    DoorsOpen() = default;
};
extern const DoorsOpen DOORS_OPEN;
extern const std::shared_ptr<const DoorsOpen> DOORS_OPEN_PTR;
// Doors Closed Declaration
class DoorsClosed : public DoorState {
    virtual std::ostream& operator<<(std::ostream& os) const;
public:
    static const DoorsClosed DOORS_CLOSED;
private:
    DoorsClosed() = default;
};
extern const DoorsClosed DOORS_CLOSED;
extern const std::shared_ptr<const DoorsClosed> DOORS_CLOSED_PTR;
// Doors Opening Declaration
class DoorsOpening : public DoorState {
    virtual std::ostream& operator<<(std::ostream& os) const;
public:
    static const DoorsOpening DOORS_OPENING;
private:
    DoorsOpening() = default;
};
extern const DoorsOpening DOORS_OPENING;
extern const std::shared_ptr<const DoorsOpening> DOORS_OPENING_PTR;
// Doors Closing Declaration
class DoorsClosing : public DoorState {
    virtual std::ostream& operator<<(std::ostream& os) const;
public:
    static const DoorsClosing DOORS_CLOSING;
private:
    DoorsClosing() = default;
};
extern const DoorsClosing DOORS_CLOSING;
extern const std::shared_ptr<const DoorsClosing> DOORS_CLOSING_PTR
#endif // DOORSTATE_H