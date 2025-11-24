/* Bank.cpp
 * Implementation of the Bank class for Elevator Simulator
 */

#include <stdexcept>

#include "Bank.h"

#include "Elevator.cpp"
#include "Passenger.cpp"

class Bank : public IBank {
    private: static const int CHECK_INTERVAL_MS = 3000;

    private:
    int floorCount;
    std::vector<Elevator*> elevators;

    const int checkIntervalMs;

    public:
    
    Bank(int numFloors = 10, int numElevators = 2, int checkInterval = CHECK_INTERVAL_MS) : floorCount(numFloors), checkIntervalMs(checkInterval) {
        if (numFloors <= 0 || numElevators <= 0) {
            throw std::invalid_argument("Number of floors and elevators must be positive.");
        }
        elevators.reserve(numElevators);
        for(int i = 0; i < numElevators; ++i) {
            elevators.push_back(new Elevator());
        }
    }
    
    // ~Bank() {
    //     // Destructor
    // }
    // Bank(const Bank& other) : floorCount(other.floorCount), checkIntervalMs(other.checkIntervalMs), elevators(other.elevators) { }

    // Bank& operator=(const Bank& other) {
    //     if (this != &other) {
    //         floorCount = other.floorCount;
    //         elevators = other.elevators;
    //     }
    //     return *this;
    // }
    
    // Bank(const Bank&& other) noexcept : floorCount(other.floorCount), checkIntervalMs(other.checkIntervalMs) {
    //     elevators = std::move(other.elevators);
    // }
    
    // Bank& operator=(const Bank&& other) noexcept {
    //     if (this != &other) {
    //         floorCount = other.floorCount;
    //         elevators = std::move(other.elevators);
    //     }
    //     return *this;
    // }

    std::future<IElevator*> ReceivePassenger(IPassenger* passenger) override {
        return std::async(std::launch::async, [&](){ 
            IElevator* closestElevator = Closest(passenger);
            closestElevator->ReceivePassenger(passenger);
            return closestElevator;
        });
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Bank& bank);

    private:

    IElevator* Closest(IPassenger* passenger) const {
        IElevator* leastDivergent = elevators.at(0);
        double leastDivergence = leastDivergent->Divergence(passenger);
        for(IElevator* elevator : elevators) {
            double divergence = elevator->Divergence(passenger);
            std::cout << "Div: " << divergence;
            if(divergence < leastDivergence) {
                leastDivergent = elevator;
                leastDivergence = divergence;
            }
        }
        return leastDivergent;
    }
};

std::ostream& operator<<(std::ostream& os, const Bank& bank) {
    os << bank.elevators.size() << " elevators." << std::endl;
    if(
        std::any_of(
            bank.elevators.begin(), bank.elevators.end(), [](const auto& elevator) { return !elevator->IsIdle(); }
        )
    ) {
        os << "\tActive elevators:" << std::endl;
    }
    for(const auto elevator : bank.elevators) {
        if(elevator->IsIdle()) { continue; }
        os << "\t" << *elevator << std::endl;
    }
    return os;
}