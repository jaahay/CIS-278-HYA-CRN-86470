// elevator/models/Elevator.cpp

#include "elevator/models/Elevator.h"
#include "elevator/services/PassengerService.h"
#include "core/Core.h"
#include "elevator/states/ElevatorStates.h"
#include <stdexcept>
#include <iostream>

namespace elevator::models {

    Elevator::Elevator(int doorDelayMs, int moveDelayMs, int currentFloor)
        : doorDelayMs_(doorDelayMs)
        , moveDelayMs_(moveDelayMs)
        , current_(currentFloor)
        , pendingPassengers_()
        , boardedPassengers_()
        , operationState_(&states::ElevatorStates::Idle())
        , doorState_(&states::ElevatorStates::Closed())
        , heading_(&states::ElevatorStates::Stationary())
        , onStateChange_(core::event::NoOpCallback<core::event::StateChangeEvent<ElevatorStateVariant>>())
    {
    }

    Elevator::Elevator(
        int doorDelayMs,
        int moveDelayMs,
        int current,
        const states::OperationState* operationState,
        const states::DoorState* doorState,
        const states::Heading* heading,
        std::list<std::shared_ptr<const Passenger>> pendingPassengers,
        std::list<std::shared_ptr<const Passenger>> boardedPassengers,
        core::StateChangeCallback<const core::event::StateChangeEvent<ElevatorStateVariant>&> onStateChange
    )
        : doorDelayMs_(doorDelayMs)
        , moveDelayMs_(moveDelayMs)
        , current_(current)
        , pendingPassengers_(std::move(pendingPassengers))
        , boardedPassengers_(std::move(boardedPassengers))
        , operationState_(operationState)
        , doorState_(doorState)
        , heading_(heading)
        , onStateChange_(std::move(onStateChange))
    {
    }

    Elevator Elevator::Transition(ElevatorStateVariant newState) const {
        auto newElevator = std::visit([this](auto&& statePtr) -> Elevator {
            if (statePtr == nullptr) {
                throw std::invalid_argument("Null pointer in ElevatorStateVariant");
            }
            using T = std::decay_t<decltype(*statePtr)>;

            if constexpr (std::is_base_of_v<detail::DoorState, T>) {
                return Elevator(doorDelayMs_, moveDelayMs_, current_, operationState_, statePtr, heading_, pendingPassengers_, boardedPassengers_, onStateChange_);
            }
            else if constexpr (std::is_base_of_v<detail::Heading, T>) {
                return Elevator(doorDelayMs_, moveDelayMs_, current_, operationState_, doorState_, statePtr, pendingPassengers_, boardedPassengers_, onStateChange_);
            }
            else if constexpr (std::is_base_of_v<detail::OperationState, T>) {
                return Elevator(doorDelayMs_, moveDelayMs_, current_, statePtr, doorState_, heading_, pendingPassengers_, boardedPassengers_, onStateChange_);
            }
            else {
                throw std::logic_error("Unhandled Elevator state type");
            }
            }, newState);

        if (newElevator.onStateChange_) {
            core::events::StateChangeEvent<Elevator, ElevatorStateVariant> event(newElevator, newState);
            newElevator.onStateChange_(event);
        }

        return newElevator;
    }

    Elevator Elevator::AddCallback(const core::event::StateChangeCallback<const core::event::StateChangeEvent<ElevatorStateVariant>&>& callback) const {
        return Elevator(doorDelayMs_, moveDelayMs_, current_, operationState_, doorState_, heading_, pendingPassengers_, boardedPassengers_, callback);
    }

    bool Elevator::IsIdle() const {
        return operationState_ == &states::ElevatorStates::Idle();
    }

    bool Elevator::PassedOrigin(const Passenger& passenger) const {
        return services::PassengerService::PassedOrigin(*this, passenger);
    }

    bool Elevator::PassedDestination(const Passenger& passenger) const {
        return services::PassengerService::PassedDestination(*this, passenger);
    }

    std::ostream& operator<<(std::ostream& os, const Elevator& elevator) {
        os << "Elevator at floor " << elevator.CurrentFloor()
            << ", OperationState: " << (elevator.IsIdle() ? "Idle" : "Active");
        return os;
    }

} // namespace elevator::models
