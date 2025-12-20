#ifndef ACTIVESTATE_H
#define ACTIVESTATE_H
#include <ostream>
template<typename Derived>
class ActiveState {
public:
    auto operator<=>(const ActiveState&) const = default;
    bool operator==(const ActiveState&) const = default;
    virtual std::ostream& operator<<(std::ostream&) const = 0;
    template<typename Friend>
    friend std::ostream& operator<<(std::ostream&, const ActiveState<Friend>&);
protected:
    ActiveState() = default;
};
class Idle : public ActiveState<Idle> {
    std::ostream& operator<<(std::ostream&) const;
public:
    static const Idle IDLE;
private:
    Idle() = default;
};
extern const Idle IDLE;
class Active : public ActiveState<Active> {
    std::ostream& operator<<(std::ostream&) const;
public:
    static const Active ACTIVE;
private:
    Active() = default;
};
extern const Active ACTIVE;
#endif // ACTIVESTATE_H