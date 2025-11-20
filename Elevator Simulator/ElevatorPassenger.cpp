#include <iostream>

#include "Passenger.h"

class Floor : public IPosition {
    private:
    int num;

    public:
    std::ostream& operator<<(std::ostream& os) const override {
        os << "Floor: " << num;
        return os;
    }
};

template <typename T>
class ElevatorPassenger : public IPassenger {
    private:
    const Floor* originFloor;
    const Floor* destinationFloor;

    public:
    ElevatorPassenger(const Floor* origin, const Floor* destination)
        : originFloor(origin), destinationFloor(destination) {}

    ~ElevatorPassenger() {}

    ElevatorPassenger(const ElevatorPassenger& other)
        : originFloor(other.originFloor), destinationFloor(other.destinationFloor) {}

    ElevatorPassenger& operator=(const ElevatorPassenger& other) {
        if (this != &other) {
            originFloor = other.originFloor;
            destinationFloor = other.destinationFloor;
        }
        return *this;
    }

    ElevatorPassenger(ElevatorPassenger&& other) noexcept
        : originFloor(other.originFloor), destinationFloor(other.destinationFloor) {}

    ElevatorPassenger& operator=(ElevatorPassenger&& other) noexcept {
        if (this != &other) {
            originFloor = other.originFloor;
            destinationFloor = other.destinationFloor;
        }
        return *this;
    }

    std::ostream& operator<<(std::ostream& os) const override {
        os << "Origin: " << originFloor;
        os << "Destination: " << destinationFloor;
        return os;
    }

    T* origin() const override { return originFloor; }
    T* destination() const override { return destinationFloor; }
};
