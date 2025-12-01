/* Bank.cpp
 * Implementation of the Bank class for Elevator Simulator
 */

#include <stdexcept>

#include "../include/Bank.h"

#include "Elevator.cpp"
#include "Passenger.cpp"

class Bank : public IBank {

    private:
    int floorCount;
    std::vector<IElevator *> elevators;

    public:
    
    Bank(std::vector<IElevator *> elevators, int numFloors = 10) : elevators(elevators), floorCount(numFloors) {
        if (numFloors <= 0) {
            throw std::invalid_argument("Number of floors and elevators must be positive.");
        }
        if (elevators.size() == 0) {
            throw std::invalid_argument("Must have at least one elevator to function.");
        }
    }
    
    ~Bank() { }

    Bank(const Bank& other) : floorCount(other.floorCount), elevators(other.elevators) { }

    Bank& operator=(const Bank&) = delete;
    
    Bank(const Bank&& other) noexcept : floorCount(other.floorCount), elevators(other.elevators) { }
    
    Bank& operator=(const Bank&&) noexcept = delete;

    friend const int ClosestIdx(const Bank &, const IPassenger &);

    IElevator &ReceivePassenger(const IPassenger &passenger) override {
        auto closestIt = ClosestIdx(*this, passenger);
        auto closest = elevators.at(closestIt);
        std::cout << "Closest elevator found as: " << std::endl << "\t";
        closest->print(std::cout);
        std::cout << std::endl;
        auto q = closest->ReceivePassenger(passenger);;
        return *closest;
    }
    
    const std::ostream& print(std::ostream& os) const override {
        os << "Elevator bank status: ";
        if(
            std::any_of(
                elevators.begin(), elevators.end(), [](const IElevator* elevator) { return !elevator->IsIdle(); }
            )
        ) {
            os << "active. Active elevators:" << std::endl;
        } else {
            os << "inactive." << std::endl;
        }
        for(const auto& e : elevators) {
            if(!e->IsIdle()) {
                os << "\t";
                e->print(os);
                os << std::endl;
            }
        }
        return os;
    }
};

const int ClosestIdx(const Bank &bank, const IPassenger &passenger) {
    int idx = 0;
    auto leastDivergence = bank.elevators.at(idx)->Divergence(passenger);
    for(int i = 0; i < bank.elevators.size(); ++i) {
        auto divergence = bank.elevators.at(i)->Divergence(passenger);
        // std::cout << "Div: " << divergence;
        if(divergence < leastDivergence) {
            idx = i;
            leastDivergence = divergence;
        }
    }
    return idx;
}