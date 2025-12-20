#ifndef PASSENGER_H
#define PASSENGER_H
#include <iostream>
#include "Heading.h"
class Passenger {
private:
    const int origin;
    const int destination;
public:
    constexpr int Origin() const;
    constexpr int Destination() const;
    template<typename HeadingType>
    constexpr bool GoingMyWay(const Heading<HeadingType>&) const;
    friend std::ostream& operator<<(std::ostream&, const Passenger&);

    Passenger(int origin, int destination);
    ~Passenger() = default;
    Passenger(const Passenger& other) = default;
    Passenger& operator=(const Passenger&) = delete;
    Passenger(Passenger&& other) noexcept = default;
    Passenger& operator=(Passenger&&) = delete;
    auto operator<=>(const Passenger &) const = default;
 };
 #endif // PASSENGER_H