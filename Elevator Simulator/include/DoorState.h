#ifndef DOORSTATE_H
#define DOORSTATE_H
#include <ostream>
template<typename Derived>
class DoorState {
public:
    auto operator<=>(const DoorState&) const = default;
    bool operator==(const DoorState&) const = default;
    virtual std::ostream& operator<<(std::ostream& os) const = 0;
    template<typename Friend>
    friend std::ostream& operator<<(std::ostream&, const Friend&);
};
class DoorsOpening : public DoorState<DoorsOpening> {
    virtual std::ostream& operator<<(std::ostream& os) const;
public:
    static const DoorsOpening DOORS_OPENING;
private:
    DoorsOpening() = default;
};
extern const DoorsOpening DOORS_OPENING;
class DoorsOpen : public DoorState<DoorsOpen> {
    virtual std::ostream& operator<<(std::ostream& os) const;
public:
    static const DoorsOpen DOORS_OPEN;
private:
    DoorsOpen() = default;
};
extern const DoorsOpen DOORS_OPEN;
class DoorsClosing : public DoorState<DoorsClosing> {
    virtual std::ostream& operator<<(std::ostream& os) const;
public:
    static const DoorsClosing DOORS_CLOSING;
private:
    DoorsClosing() = default;
};
extern const DoorsClosing DOORS_CLOSING;
class DoorsClosed : public DoorState<DoorsClosed> {
    virtual std::ostream& operator<<(std::ostream& os) const;
public:
    static const DoorsClosed DOORS_CLOSED;
private:
    DoorsClosed() = default;
};
extern const DoorsClosed DOORS_CLOSED;
#endif // DOORSTATE_H