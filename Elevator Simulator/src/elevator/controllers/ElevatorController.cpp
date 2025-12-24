// elevator/controllers/ElevatorController.cpp
#include "elevator/controllers/ElevatorController.h"

namespace elevator::controllers {

    ElevatorController::ElevatorController(elevator::ElevatorService& service)
        : service_(service)
    {
    }

    std::future<elevator::Elevator> ElevatorController::AddPassenger(const Passenger& passenger) {
        return service_.AddPassenger(passenger);
    }

    std::future<elevator::Elevator> ElevatorController::Move() {
        return service_.Move();
    }

    void ElevatorController::Wait(std::chrono::milliseconds timeout) {
        service_.Wait(timeout);
    }

    elevator::Elevator ElevatorController::GetElevator() const {
        return service_.GetElevator();
    }

} // namespace elevator::controllers
