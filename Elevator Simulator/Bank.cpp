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
    Bank(const Bank& other) : floorCount(other.floorCount), checkIntervalMs(other.checkIntervalMs) {
        int numElevators = other.elevators.size();
        elevators.resize(numElevators);
        for (int i = 0; i < numElevators; ++i) {
            elevators[i] = other.elevators[i];
        }
    }
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

    std::future<IElevator*> CallElevator(int floor) {
        if (floor < 1 || floor > floorCount) {
            throw std::out_of_range("Requested floor is out of range.");
        }
       
        return std::async(std::launch::async, [this, floor]() -> IElevator* {
            int range = floorCount + 1;
            std::cout << "Searching for an idle elevator to service floor " << floor << "..." << std::endl;
            IElevator* called = nullptr;
            while (called == nullptr) {
                for (int i = 0; i < elevators.size(); ++i) {
                    Elevator& elevator = elevators[i];
                    if (elevator.IsIdle()) {
                        // std::cout << "Elevator " << i + 1 << " is idle at floor " << elevator.GetCurrentFloor() << "." << std::endl;
                        if (elevator.GetCurrentFloor() == floor) {
                            std::cout << "Elevator " << i + 1 << " is already at the requested floor." << std::endl;
                            return &elevator;
                        } else if( abs(elevator.GetCurrentFloor() - floor) < range ) {
                            range = abs(elevator.GetCurrentFloor() - floor);
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
            called->MoveToFloor(floor);
            return called;
        });
    }

    void Report(std::ostream& out, size_t bufferSize) const override {
        for (int i = 0; i < elevators.size(); ++i) {
            out << "Elevator " << std::to_string(i + 1) << ": Current Floor " << std::to_string(elevators[i].GetCurrentFloor());
            out << (elevators[i].IsIdle() ? " (Idle)\n" : " (Active)\n");
        }
    }

    void toString(char* buffer, size_t bufferSize) const override {
        std::string status = "Bank Status:\n";
        for (int i = 0; i < elevators.size(); ++i) {
            status += "Elevator " + std::to_string(i + 1) + ": Current Floor " + std::to_string(elevators[i].GetCurrentFloor());
            status += elevators[i].IsIdle() ? " (Idle)\n" : " (Active)\n";
        }
        strncpy_s(buffer, bufferSize, status.c_str(), bufferSize - 1);
        buffer[bufferSize - 1] = '\0'; // Ensure null-termination
    }
};

std::ostream& operator<<(std::ostream& os, const Bank& bank) {
    char buffer[1024];
    bank.toString(buffer, sizeof(buffer));
    os << buffer;
    return os;
}