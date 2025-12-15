#ifndef ACTIVESTATE_H
#define ACTIVESTATE_H
class ActiveState {
public:
    auto operator<=>(const ActiveState&) const = default;
};
extern ActiveState* IDLE;
extern ActiveState* ACTIVE;
#endif // ACTIVESTATE_H