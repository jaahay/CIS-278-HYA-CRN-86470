/* Bank.cpp
 * Implementation of the Bank class for Elevator Simulator
 */

#include "Bank.h"
#include <iostream>
#include <stdexcept>
#include <vector>

class BankImpl : public Bank {
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
            ElevatorPtr[i]->MoveToFloor(other.ElevatorPtr[i]->Floor());
        }
    }
    BankImpl& operator=(const BankImpl& other) {
        if (this != &other) {
            delete[] ElevatorPtr;
            floorCount = other.floorCount;
            int numElevators = other.ElevatorPtr ? sizeof(other.ElevatorPtr) / sizeof(Elevator*) : 0;
            ElevatorPtr = new Elevator*[numElevators];
            for (int i = 0; i < numElevators; ++i) {
                ElevatorPtr[i]->MoveToFloor(other.ElevatorPtr[i]->Floor());
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
        // TODO: implement elevator selection logic
        return nullptr;
    }
};