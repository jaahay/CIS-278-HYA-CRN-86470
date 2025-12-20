#ifndef HEADING_H
#define HEADING_H
#include <ostream>
template<typename Derived>
class Heading {
public:
    auto operator<=>(const Heading&) const = default;
    bool operator==(const Heading&) const = default;
    virtual std::ostream& operator<<(std::ostream&) const = 0;
    friend std::ostream& operator<<(std::ostream&, const Heading<Derived>&);
protected:
    Heading() = default;
};
class GoingUp : public Heading<GoingUp> {
    std::ostream& operator<<(std::ostream&) const;
public:
    static const GoingUp GOING_UP;
private:
    GoingUp() = default;
};
extern const GoingUp GOING_UP;
class GoingDown : public Heading<GoingDown> {
    std::ostream& operator<<(std::ostream&) const;
public:
    static const GoingDown GOING_DOWN;
private:
    GoingDown() = default;
};
extern const GoingDown GOING_DOWN;
class Stopped : public Heading<Stopped> {
    std::ostream& operator<<(std::ostream&) const;
public:
    static const Stopped STOPPED;
private:
    Stopped() = default;
};
extern const Stopped STOPPED;
#endif // !HEADING_H