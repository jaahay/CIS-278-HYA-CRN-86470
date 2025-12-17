#ifndef HEADING_H
#define HEADING_H
#include <ostream>
class Heading {
public:
    auto operator<=>(const Heading&) const = default;
    bool operator==(const Heading&) const = default;
    virtual std::ostream& operator<<(std::ostream&) const = 0;
    friend std::ostream& operator<<(std::ostream&, const Heading&);
//private:
    //Heading();
};
class GoingUp : public Heading {
    virtual std::ostream& operator<<(std::ostream&) const;
//private:
//    GoingUp();
};
extern const GoingUp GOING_UP;
class GoingDown : public Heading {
    virtual std::ostream& operator<<(std::ostream&) const;
};
extern const GoingDown GOING_DOWN;
class Stopped : public Heading {
    virtual std::ostream& operator<<(std::ostream&) const;
};
extern const Stopped STOPPED;
#endif // !HEADING_H