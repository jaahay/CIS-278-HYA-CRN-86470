/* Bank.cpp
 * Implementation of the Bank class for Elevator Simulator
 */

#include <chrono>
#include <future>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#include "Bank.h"

#include "Elevator.cpp"

class Bank : public IBank {
    private: static const int CHECK_INTERVAL_MS = 3000;

    private:
    int floorCount;
    std::vector<Elevator> elevators;

    const int checkIntervalMs;

    public:
    
    Bank(int numFloors = 10, int numElevators = 2, int checkInterval = CHECK_INTERVAL_MS) : floorCount(numFloors), checkIntervalMs(checkInterval) {
        if (numFloors <= 0 || numElevators <= 0) {
            throw std::invalid_argument("Number of floors and elevators must be positive.");
        }
        elevators.resize(numElevators);
    }
    
    ~Bank() {
        // Destructor
    }
    Bank(const Bank& other) : floorCount(other.floorCount), checkIntervalMs(other.checkIntervalMs), elevators(other.elevators) { }

    Bank& operator=(const Bank& other) {
        if (this != &other) {
            floorCount = other.floorCount;
            elevators = other.elevators;
        }
        return *this;
    }
    
    Bank(const Bank&& other) noexcept : floorCount(other.floorCount), checkIntervalMs(other.checkIntervalMs) {
        elevators = std::move(other.elevators);
    }
    
    Bank& operator=(const Bank&& other) noexcept {
        if (this != &other) {
            floorCount = other.floorCount;
            elevators = std::move(other.elevators);
        }
        return *this;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Bank& bank);

    std::future<IElevator*> CallElevator(int floor) {
        if (floor < 1 || floor > floorCount) {
            throw std::out_of_range("Requested floor is out of range.");
        }
       
        return std::async(std::launch::async, [this, floor]() -> IElevator* {
            int range = floorCount + 1;
            std::cout << "Searching for an idle elevator to service floor " << floor << "..." << std::endl;
            IElevator* called = nullptr;
            while (called == nullptr) {
                for(auto& elevator : elevators) {
                    if (elevator.IsIdle()) {
                        if (elevator.CurrentFloor() == floor) {
                            std::cout << "Elevator is already at the requested floor." << std::endl;
                            return &elevator;
                        } else if ( std::abs(elevator.CurrentFloor() - floor) < range ) {
                            range = std::abs(elevator.CurrentFloor() - floor);
                            called = &elevator;
                        }
                    }
                }
                if(called == nullptr) {
                    std::cout << "No idle elevators available to service floor " << floor << ". Retrying in " << checkIntervalMs << " ms..." << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(checkIntervalMs));
                } else {
                    std::cout << "Elevator selected to service floor " << floor << "." << std::endl;
                }
            }
            called->RequestFloor(floor);
            return called;
        });
    }
};

std::ostream& operator<<(std::ostream& os, const Bank& bank) {
    for(const auto& elevator : bank.elevators) {
        os << elevator << std::endl;
    }
    return os;
}