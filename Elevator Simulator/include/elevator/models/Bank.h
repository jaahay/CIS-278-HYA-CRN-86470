#ifndef BANK_H
#define BANK_H

#include "Elevator.h"

template<class Elevator, class Passenger>
class Bank {
protected:
    int floorCount;

    std::vector<Elevator*> elevators;
public:
    Elevator& ReceivePassenger(const Passenger&) const;
    const int ClosestIdx(const Passenger&) const;

    friend std::ostream& operator<<(std::ostream& os, const Bank& bank) {
        os << "Elevator bank status: ";
        if (
            std::any_of(
                bank.elevators.begin(), bank.elevators.end(), [](const Elevator* elevator) { return !elevator->IsIdle(); }
            )
            ) {
            os << "active. Active elevators:" << std::endl;
        }
        else {
            os << "inactive." << std::endl;
        }
        for (const auto& elevator : bank.elevators) {
            if (!elevator->IsIdle()) {
                os << "\t" << elevator << std::endl;
            }
        }
        return os;
    };

    Bank(std::vector<Elevator*> elevators, int numFloors) : elevators(elevators), floorCount(numFloors) {
        if (numFloors <= 0) {
            throw std::invalid_argument("Number of floors and elevators must be positive.");
        }
        if (elevators.size() == 0) {
            throw std::invalid_argument("Must have at least one elevator to function.");
        }
    }
    ~Bank() = default;
    Bank(const Bank& other) : floorCount(other.floorCount), elevators(other.elevators) {}
    Bank& operator=(const Bank&) = delete;
    Bank(const Bank&& other) noexcept : floorCount(other.floorCount), elevators(other.elevators) {}
};


#endif // BANK_H
