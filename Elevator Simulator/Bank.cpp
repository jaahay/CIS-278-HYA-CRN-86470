/* Bank.cpp
 * Implementation of the Bank class for Elevator Simulator
 */

#include <chrono>
#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <vector>

#include "Bank.h"

#include "Elevator.cpp"

class Bank : public IBank {
    private: static const int CHECK_INTERVAL_MS = 100;

    private:
    int floorCount;
    Elevator* elevatorPtr;

    const int checkIntervalMs;

    public:
    Bank(int numFloors = 10, int numElevators = 2, int checkInterval = CHECK_INTERVAL_MS) : floorCount(numFloors), checkIntervalMs(checkInterval) {
        if (numFloors <= 0 || numElevators <= 0) {
            throw std::invalid_argument("Number of floors and elevators must be positive.");
        }
        elevatorPtr = new Elevator[numElevators];
    }
    ~Bank() {
        delete[] elevatorPtr;
    }
    Bank(const Bank& other) : floorCount(other.floorCount), checkIntervalMs(other.checkIntervalMs) {
        int numElevators = other.elevatorPtr ? sizeof(other.elevatorPtr) / sizeof(Elevator*) : 0;
        elevatorPtr = new Elevator[numElevators];
        for (int i = 0; i < numElevators; ++i) {
            elevatorPtr[i] = other.elevatorPtr[i];
        }
    }
    Bank& operator=(const Bank& other) {
        if (this != &other) {
            delete[] elevatorPtr;
            floorCount = other.floorCount;

            int numElevators = other.elevatorPtr ? sizeof(other.elevatorPtr) / sizeof(Elevator*) : 0;
            elevatorPtr = new Elevator[numElevators];
            for (int i = 0; i < numElevators; ++i) {
                elevatorPtr[i] = other.elevatorPtr[i];
            }
        }
        return *this;
    }
    Bank(const Bank&& other) noexcept : floorCount(other.floorCount), elevatorPtr(other.elevatorPtr), checkIntervalMs(other.checkIntervalMs) {
        delete[] other.elevatorPtr;
    }
    Bank& operator=(const Bank&& other) noexcept {
        if (this != &other) {
            delete[] elevatorPtr;
            floorCount = other.floorCount;
            elevatorPtr = other.elevatorPtr;
            delete[] other.elevatorPtr;
        }
        return *this;
    }

    std::future<IElevator*> CallElevator(int floor) const {
        if (floor < 1 || floor > floorCount) {
            throw std::out_of_range("Requested floor is out of range.");
        }
        std::cout << "Calling elevator to floor " << floor << "..." << std::endl;

        return std::async(std::launch::async, [this, floor]() {
            IElevator* elPtr = nullptr;
            while(elPtr == nullptr) {
                int range = floorCount;
                for (size_t i = 0; i < sizeof(elevatorPtr) / sizeof(IElevator*) + 1; ++i) {
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
        });
    }

    void toString(char* buffer, size_t bufferSize) const override {
        strncpy(buffer, "Bank status:", bufferSize);
        if (bufferSize > 0) buffer[bufferSize - 1] = '\0';
        char elevatorBuffer[100];
        for (size_t i = 0; i < sizeof(elevatorPtr) / sizeof(IElevator*) + 1; ++i) {
            elevatorPtr[i].toString(elevatorBuffer, sizeof(elevatorBuffer));
            strncat(buffer, "\n", bufferSize - strlen(buffer) - 1);
            strncat(buffer, elevatorBuffer, bufferSize - strlen(buffer) - 1);
        }
    }
};