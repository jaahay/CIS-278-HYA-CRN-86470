// elevator/models/Elevator.h
#ifndef ELEVATOR_MODELS_ELEVATOR_H
#define ELEVATOR_MODELS_ELEVATOR_H

#include <compare>
#include <future>
#include <iostream>
#include <list>
#include <memory>

#include "core/event/StateChangeCallback.h"
#include "core/event/StateChangeEvent.h"
#include "elevator/states/ElevatorStateVariants.h"
#include "elevator/models/Passenger.h"

namespace elevator::models {

    class ElevatorService; // Forward declare friend class

    class Elevator {
    public:
        explicit Elevator(int doorDelayMs = 1000, int moveDelayMs = 500, int currentFloor = 1);

        Elevator(const Elevator&) = default;
        Elevator& operator=(const Elevator&) = default;
        Elevator(Elevator&&) noexcept = default;
        Elevator& operator=(Elevator&&) noexcept = default;

        auto operator<=>(const Elevator&) const = default;

        // Transition to a new elevator state variant (pure, immutable)
        Elevator Transition(states::ElevatorStateVariant newState) const;

        Elevator AddCallback(
            const core::event::StateChangeCallback<const core::event::StateChangeEvent<states::ElevatorStateVariant>&>&) const;

        // Public const accessors
        constexpr int CurrentFloor() const { return current_; }
        bool IsIdle() const;

        const std::list<std::shared_ptr<const Passenger>>& GetPendingPassengers() const { return pendingPassengers_; }
        const std::list<std::shared_ptr<const Passenger>>& GetBoardedPassengers() const { return boardedPassengers_; }

        const states::OperationState* GetOperationState() const { return operationState_; }
        const states::DoorState* GetDoorState() const { return doorState_; }
        const states::Heading* GetHeading() const { return heading_; }

        friend std::ostream& operator<<(std::ostream&, const Elevator&);

    private:
        friend class ElevatorService;

        // Private constructor for internal state transitions
        Elevator(
            int doorDelayMs,
            int moveDelayMs,
            int current,
            const states::OperationState* operationState,
            const states::DoorState* doorState,
            const states::Heading* heading,
            std::list<std::shared_ptr<const Passenger>> pendingPassengers,
            std::list<std::shared_ptr<const Passenger>> boardedPassengers,
            core::event::StateChangeCallback<const core::event::StateChangeEvent<elevator::states::ElevatorStateVariant>&> onStateChange
        );

        // Private immutable members
        const int doorDelayMs_;
        const int moveDelayMs_;
        const int current_;

        const std::list<std::shared_ptr<const Passenger>> pendingPassengers_;
        const std::list<std::shared_ptr<const Passenger>> boardedPassengers_;

        const elevator::states::OperationState* const operationState_;
        const elevator::states::DoorState* const doorState_;
        const elevator::states::Heading* const heading_;

        const core::event::StateChangeCallback<core::event::StateChangeEvent<elevator::states::ElevatorStateVariant>> onStateChange_;
    };

} // namespace elevator::models

#endif // ELEVATOR_MODELS_ELEVATOR_H
