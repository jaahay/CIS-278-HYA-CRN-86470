#include <iostream>

#include "Passenger.h"

class ElevatorPassenger : public IPassenger {
    private:
    const int* origin;
    const int* destination;

    public:
    ElevatorPassenger(const int* origin, const int* destination)
        : origin(origin), destination(destination) {}

    ~ElevatorPassenger() {}

    ElevatorPassenger(const ElevatorPassenger& other)
        : origin(other.origin), destination(other.destination) {}

    ElevatorPassenger& operator=(const ElevatorPassenger& other) {
        if (this != &other) {
            origin = other.origin;
            destination = other.destination;
        }
        return *this;
    }

    ElevatorPassenger(ElevatorPassenger&& other) noexcept
        : origin(other.origin), destination(other.destination) {}

    ElevatorPassenger& operator=(ElevatorPassenger&& other) noexcept {
        if (this != &other) {
            origin = other.origin;
            destination = other.destination;
        }
        return *this;
    }

    std::ostream& operator<<(std::ostream& os) const override {
        os << "Origin: " << origin;
        os << "Destination: " << destination;
        return os;
    }

    const int* origin() const { return origin; }
    const int* destination() const { return destination; }
};
