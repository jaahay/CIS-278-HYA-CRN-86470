#ifndef ACTIVESTATE_H
#define ACTIVESTATE_H
#include <ostream>
class ActiveState {
public:
    auto operator<=>(const ActiveState&) const = default;
    bool operator==(const ActiveState&) const = default;
    virtual std::ostream& operator<<(std::ostream&) const = 0;
    friend std::ostream& operator<<(std::ostream&, const ActiveState&);
};
class Idle : public ActiveState {
public:
    virtual std::ostream& operator<<(std::ostream& os) const;
};
const extern Idle IDLE;
class Active : public ActiveState {
public:
    virtual std::ostream& operator<<(std::ostream& os) const;
};
const extern Active ACTIVE;
#endif // ACTIVESTATE_H