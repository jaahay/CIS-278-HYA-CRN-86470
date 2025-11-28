/* Bank.cpp
 * Implementation of the Bank class for Elevator Simulator
 */

#include <stdexcept>

#include "Bank.h"

#include "Elevator.cpp"
#include "Passenger.cpp"

class Bank : public IBank {

    private:
    int floorCount;
    std::vector<IElevator *> elevators;

    public:
    
    Bank(std::vector<IElevator *> elevators, int numFloors = 10, int checkInterval = CHECK_INTERVAL_MS) : elevators(elevators), floorCount(numFloors) {
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

    IElevator &ReceivePassenger(const IPassenger &passenger) override {
        auto closest = &Closest(passenger);
        std::cout << "Closest elevator found as: " << std::endl << "\t";
        closest->print(std::cout);
        std::cout << std::endl;
        auto q = closest->ReceivePassenger(passenger);
        return *closest;
    }
    
    const std::ostream& print(std::ostream& os) const override {
        os << "Elevator bank status: " << std::endl;
        if(
            std::any_of(
                elevators.begin(), elevators.end(), [](const IElevator* elevator) { return !elevator->IsIdle(); }
            )
        ) {
            os << "\tactive. Active elevators:" << std::endl;
        } else {
            os << "\tinactive." << std::endl;
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

    private:

    IElevator &Closest(const IPassenger &passenger) {
        IElevator *leastDivergent = elevators.at(0);
        auto leastDivergence = leastDivergent->Divergence(passenger);
        for(IElevator *elevator : elevators) {
            auto divergence = elevator->Divergence(passenger);
            // std::cout << "Div: " << divergence;
            if(divergence < leastDivergence) {
                leastDivergent = elevator;
                leastDivergence = divergence;
            }
        }
        return *leastDivergent;
    }
};

