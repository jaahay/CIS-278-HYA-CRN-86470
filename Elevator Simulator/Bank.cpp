/* Bank.cpp
 * Implementation of the Bank class for Elevator Simulator
 */

#include "Bank.h"
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <vector>

class BankImpl : public Bank {
    private: static const int CHECK_INTERVAL_MS = 100;

    private:
    int floorCount;
    Elevator** ElevatorPtr;

    public:
    BankImpl(int numFloors, int numElevators) : floorCount(numFloors) {
        if (numFloors <= 0 || numElevators <= 0) {
            throw std::invalid_argument("Number of floors and elevators must be positive.");
        }
        ElevatorPtr = new Elevator*[numElevators];
    }
    ~BankImpl() {
        delete[] ElevatorPtr;
    }
    BankImpl(const BankImpl& other) : floorCount(other.floorCount) {
        int numElevators = other.ElevatorPtr ? sizeof(other.ElevatorPtr) / sizeof(Elevator*) : 0;
        ElevatorPtr = new Elevator*[numElevators];
        for (int i = 0; i < numElevators; ++i) {
            ElevatorPtr[i] = other.ElevatorPtr[i];
        }
    }
    BankImpl& operator=(const BankImpl& other) {
        if (this != &other) {
            delete[] ElevatorPtr;
            floorCount = other.floorCount;
            int numElevators = other.ElevatorPtr ? sizeof(other.ElevatorPtr) / sizeof(Elevator*) : 0;
            ElevatorPtr = new Elevator*[numElevators];
            for (int i = 0; i < numElevators; ++i) {
                ElevatorPtr[i] = other.ElevatorPtr[i];
            }
        }
        return *this;
    }
    BankImpl(const BankImpl&& other) noexcept : floorCount(other.floorCount), ElevatorPtr(other.ElevatorPtr) {
        delete[] other.ElevatorPtr;
    }
    BankImpl& operator=(const BankImpl&& other) noexcept {
        if (this != &other) {
            delete[] ElevatorPtr;
            floorCount = other.floorCount;
            ElevatorPtr = other.ElevatorPtr;
            delete[] other.ElevatorPtr;
        }
        return *this;
    }

    Elevator* CallElevator() {
        Elevator* elevator = nullptr;
        while(elevator == nullptr) {
            for (size_t i = 0; i < sizeof(ElevatorPtr) / sizeof(Elevator*); ++i) {
                if (ElevatorPtr[i]->IsIdle()) {
                    elevator = ElevatorPtr[i];
                    break;
                }
            }
            if (elevator == nullptr) {
                std::this_thread::sleep_for(std::chrono::milliseconds(CHECK_INTERVAL_MS));
            }
        }
        return elevator;
    }
};