// elevator/controllers/ElevatorController.h
#ifndef ELEVATOR_CONTROLLERS_ELEVATOR_CONTROLLER_H
#define ELEVATOR_CONTROLLERS_ELEVATOR_CONTROLLER_H

#include <future>
#include "elevator/services/ElevatorService.h"

namespace elevator::controllers {

    class ElevatorController {
    public:
        explicit ElevatorController(elevator::ElevatorService& service);

        std::future<elevator::Elevator> AddPassenger(const Passenger& passenger);
        std::future<elevator::Elevator> Move();
        void Wait(std::chrono::milliseconds timeout = std::chrono::seconds(10));
        elevator::Elevator GetElevator() const;

    private:
        elevator::ElevatorService& service_;
    };

} // namespace elevator::controllers

#endif // ELEVATOR_CONTROLLERS_ELEVATOR_CONTROLLER_H
