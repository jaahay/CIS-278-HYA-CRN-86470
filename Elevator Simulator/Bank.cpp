/* Bank.cpp
 * Implementation of the Bank class for Elevator Simulator
 */

#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <vector>

#include "Bank.h"

#include "Elevator.cpp"

class BankImpl : public Bank {
    private: static const int CHECK_INTERVAL_MS = 100;

    private:
    int floorCount;
    ElevatorImpl* elevatorPtr;

    const int checkIntervalMs;

    public:
    BankImpl(int numFloors, int numElevators, int checkInterval = CHECK_INTERVAL_MS) : floorCount(numFloors), checkIntervalMs(checkInterval) {
        if (numFloors <= 0 || numElevators <= 0) {
            throw std::invalid_argument("Number of floors and elevators must be positive.");
        }
        elevatorPtr = new ElevatorImpl[numElevators];
    }
    ~BankImpl() {
        delete[] elevatorPtr;
    }
    BankImpl(const BankImpl& other) : floorCount(other.floorCount), checkIntervalMs(other.checkIntervalMs) {
        int numElevators = other.elevatorPtr ? sizeof(other.elevatorPtr) / sizeof(Elevator*) : 0;
        elevatorPtr = new ElevatorImpl[numElevators];
        for (int i = 0; i < numElevators; ++i) {
            elevatorPtr[i] = other.elevatorPtr[i];
        }
    }
    BankImpl& operator=(const BankImpl& other) {
        if (this != &other) {
            delete[] elevatorPtr;
            floorCount = other.floorCount;

            int numElevators = other.elevatorPtr ? sizeof(other.elevatorPtr) / sizeof(Elevator*) : 0;
            // elevatorPtr = new ElevatorImpl[numElevators];
            for (int i = 0; i < numElevators; ++i) {
                elevatorPtr[i] = other.elevatorPtr[i];
            }
        }
        return *this;
    }
    BankImpl(const BankImpl&& other) noexcept : floorCount(other.floorCount), elevatorPtr(other.elevatorPtr), checkIntervalMs(other.checkIntervalMs) {
        delete[] other.elevatorPtr;
    }
    BankImpl& operator=(const BankImpl&& other) noexcept {
        if (this != &other) {
            delete[] elevatorPtr;
            floorCount = other.floorCount;
            elevatorPtr = other.elevatorPtr;
            delete[] other.elevatorPtr;
        }
        return *this;
    }

    Elevator* CallElevator(int floor) const override{
        if (floor < 1 || floor > floorCount) {
            throw std::out_of_range("Requested floor is out of range.");
        }
        std::cout << "Calling elevator to floor " << floor << "..." << std::endl;
        ElevatorImpl* elPtr = nullptr;
        while(elPtr == nullptr) {
            int range = floorCount;
            for (size_t i = 0; i < sizeof(elevatorPtr) / sizeof(Elevator*); ++i) {
                std::cout << "Checking elevator " << i + 1 << "..." << std::endl;
                if (elevatorPtr[i].IsIdle()) {
                    std::cout << "Elevator " << i + 1 << " is idle at floor " << elevatorPtr[i].GetCurrentFloor() << "." << std::endl;
                    if( abs(elevatorPtr[i].GetCurrentFloor() - floor) < range ) {
                        range = abs(elevatorPtr[i].GetCurrentFloor() - floor);
                        elPtr = &elevatorPtr[i];
                    }
                }
            }
            if (elPtr == nullptr) {
                std::this_thread::sleep_for(std::chrono::milliseconds(CHECK_INTERVAL_MS));
            }
        }
        elPtr->MoveToFloor(floor);
        return elPtr;
    }
};