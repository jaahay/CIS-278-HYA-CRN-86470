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
    
    
    
    
    IElevator* Closest(const IPassenger& passenger) const {
        Elevator* leastDivergent = elevators.at(0);
        double leastDivergence = leastDivergent->Divergence(passenger);
        for(Elevator* elevator : elevators) {
            double divergence = elevator->Divergence(passenger);
            if(divergence < leastDivergence) {
                leastDivergent = elevator;
                leastDivergence = divergence;
            }
        }
        return leastDivergent;
    }

    std::future<IElevator*> ReceivePassenger(const IPassenger& passenger) override {
        return std::async(std::launch::async, [&](){ return Closest(passenger); });
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Bank& bank);
};

std::ostream& operator<<(std::ostream& os, const Bank& bank) {
    for(const auto elevator : bank.elevators) {
        os << *elevator << std::endl;
    }
    return os;
}