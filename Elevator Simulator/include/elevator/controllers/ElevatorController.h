// elevator/controllers/ElevatorController.h
#ifndef ELEVATOR_CONTROLLERS_ELEVATOR_CONTROLLER_H
#define ELEVATOR_CONTROLLERS_ELEVATOR_CONTROLLER_H

#include <future>
#include "elevator/services/ElevatorService.h"

#include "elevator/models/Elevator.h"

namespace elevator::controllers {

    class ElevatorController {
    public:
        explicit ElevatorController(services::ElevatorService& service);

        std::future<models::Elevator> AddPassenger(const models::Passenger& passenger);
        std::future<models::Elevator> Move();
        void Wait(std::chrono::milliseconds timeout = std::chrono::seconds(10));
        models::Elevator GetElevator() const;

    private:
        services::ElevatorService& service_;
    };

} // namespace elevator::controllers

#endif // ELEVATOR_CONTROLLERS_ELEVATOR_CONTROLLER_H
