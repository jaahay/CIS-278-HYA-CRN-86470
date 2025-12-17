#ifndef ACTIVESTATE_H
#define ACTIVESTATE_H
#include <ostream>
class ActiveState {
public:
    auto operator<=>(const ActiveState&) const = default;
    bool operator==(const ActiveState&) const = default;
    virtual std::ostream& operator<<(std::ostream&) const = 0;
    friend std::ostream& operator<<(std::ostream&, const ActiveState&);
protected:
    ActiveState() = default;
};
class Idle : public ActiveState {
public:
    static Idle const IDLE;
    virtual std::ostream& operator<<(std::ostream& os) const;
private:
    Idle() = default;
};
extern const Idle IDLE;
class Active : public ActiveState {
public:
    static Active const ACTIVE;
    virtual std::ostream& operator<<(std::ostream& os) const;
private:
    Active() = default;
};
extern const Active ACTIVE;
#endif // ACTIVESTATE_H