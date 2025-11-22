/* Bank.cpp
 * Implementation of the Bank class for Elevator Simulator
 */

#include <stdexcept>

#include "Bank.h"

// #include "Elevator.h"
// #include "Passenger.h"

// #include "Bank.cpp"
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
    
    friend std::ostream& operator<<(std::ostream& os, const Bank& bank);

    std::future<IElevator*> ReceivePassenger(const int embark, const int disembark) override {
        throw std::logic_error("not yet implemented");
        // if (floor < 1 || floor > floorCount) {
        //     throw std::out_of_range("Requested floor is out of range.");
        // }
       
        // return std::async(std::launch::async, [this, floor]() -> Elevator* {
        //     int range = floorCount + 1;
        //     std::cout << std::endl << "Searching for an idle elevator to service floor " << floor << "..." << std::endl;
        //     Elevator* called = nullptr;
        //     while (called == nullptr) {
        //         for(Elevator* elevator : elevators) {
        //             if (elevator->IsIdle()) {
        //                 if (elevator->CurrentFloor() == floor) {
        //                     std::cout << "Elevator is already at the requested floor." << std::endl;
        //                     return elevator;
        //                 } else if ( std::abs(elevator->CurrentFloor() - floor) < range ) {
        //                     range = std::abs(elevator->CurrentFloor() - floor);
        //                     called = elevator;
        //                 }
        //             }
        //         }
        //         if(called == nullptr) {
        //             std::cout << "No idle elevators available to service floor " << floor << ". Retrying in " << checkIntervalMs << " ms..." << std::endl;
        //             std::this_thread::sleep_for(std::chrono::milliseconds(checkIntervalMs));
        //         } else {
        //             std::cout << "Elevator selected to service floor " << floor << "." << std::endl;
        //         }
        //     }
        //     called->RequestFloor(floor);
        //     return called;
        // });
    }
};

std::ostream& operator<<(std::ostream& os, const Bank& bank) {
    for(const auto elevator : bank.elevators) {
        os << *elevator << std::endl;
    }
    return os;
}