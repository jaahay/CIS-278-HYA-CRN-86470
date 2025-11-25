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
    std::vector<IElevator *> elevators;

    const int checkIntervalMs;

    public:
    
    Bank(std::vector<IElevator *> elevators, int numFloors = 10, int checkInterval = CHECK_INTERVAL_MS) : elevators(elevators), floorCount(numFloors), checkIntervalMs(checkInterval) {
        if (numFloors <= 0) {
            throw std::invalid_argument("Number of floors and elevators must be positive.");
        }
        if (elevators.size() == 0) {
            throw std::invalid_argument("Must have at least one elevator to function.");
        }
        // IElevator *e = elevators.at(0);
        // std::cout << e;
        // std::cout << &elevators.at(0);
    }
    
    // ~Bank() {
    //     // delete[] elevators;
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

    IElevator &ReceivePassenger(const IPassenger &passenger) override {
        auto closest = &Closest(passenger);
        // std::cout << closest.CurrentFloor();
        // x.CurrentFloor();
        auto q = closest->ReceivePassenger(passenger);
        return *closest;
    }

    // auto it(const IPassenger &passenger) {
    //     auto r = std::async(
    //         std::launch::async,
    //         [&]{
    //         return Closest(passenger);
    //     });
    //     auto s = std::async(
    //         std::launch::async,
    //         [&](std::future<IElevator *> closestF){
    //             auto closest = closestF.get();
    //             closest->ReceivePassenger(passenger);
    //             return closest;
    //         },
    //         r
    //     );
    //     return s;
    // }

    // std::future<IElevator *> ReceivePassenger(const IPassenger &passenger) override {
    //     auto r = it(passenger);
    //     return r;
    // }
    
    const std::ostream& print(std::ostream& os) const override {
        os << elevators.size() << " elevators." << std::endl;
        if(
            std::any_of(
                elevators.begin(), elevators.end(), [](const IElevator* elevator) { return !elevator->IsIdle(); }
            )
        ) {
            os << "\tActive elevators:" << std::endl;
        }
        for(const auto& e : elevators) {
            os << "\t";
            e->print(os);
            os << std::endl;
        }
        return os;
    }

    private:

    IElevator &Closest(const IPassenger &passenger) {
        IElevator *leastDivergent = elevators.at(0);
        leastDivergent->print(std::cout);
        // &leastDivergent.print(std::cout);
        auto leastDivergence = leastDivergent->Divergence(passenger);
        // std::cout << "hoho";
        for(IElevator *elevator : elevators) {
            auto divergence = elevator->Divergence(passenger);
            // std::cout << "Div: " << divergence;
            if(divergence < leastDivergence) {
                // auto r = *elevator;
                leastDivergent = elevator;
                leastDivergence = divergence;
            }
        }
        return *leastDivergent;
    }
};

