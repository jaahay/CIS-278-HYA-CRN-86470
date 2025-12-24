// elevator/models/Passenger.h
#ifndef ELEVATOR_MODELS_PASSENGER_H
#define ELEVATOR_MODELS_PASSENGER_H
#include <iostream>
#include "elevator/states/ElevatorStates.h"

namespace elevator::models {
    class Passenger {
    private:
        const int origin;
        const int destination;
    public:
        constexpr int Origin() const;
        constexpr int Destination() const;
        const bool GoingMyWay(const elevator::detail::Heading*) const;
        friend std::ostream& operator<<(std::ostream&, const Passenger&);

        Passenger(int origin, int destination);
        ~Passenger() = default;
        Passenger(const Passenger& other) = default;
        Passenger& operator=(const Passenger&) = delete;
        Passenger(Passenger&& other) noexcept = default;
        Passenger& operator=(Passenger&&) = delete;
        auto operator<=>(const Passenger&) const = default;
    };
}
#endif // ELEVATOR_MODELS_PASSENGER_H
