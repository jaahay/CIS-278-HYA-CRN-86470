// elevator/models/Elevator.cpp

#include "elevator/models/Elevator.h"
#include <stdexcept>
#include <iostream>

namespace elevator::models {

    Elevator::Elevator(int doorDelayMs, int moveDelayMs, int currentFloor)
        : doorDelayMs_(doorDelayMs)
        , moveDelayMs_(moveDelayMs)
        , current_(currentFloor)
        , pendingPassengers_()
        , boardedPassengers_()
        , operationState_(&states::Idle())
        , doorState_(&states::Closed())
        , heading_(&states::Stopped())
        , onStateChange_(core::event::NoOpCallback<core::event::StateChangeEvent<states::ElevatorStateVariant>>())
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
        core::StateChangeCallback<const core::event::StateChangeEvent<states::ElevatorStateVariant>&> onStateChange
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

    Elevator Elevator::Transition(states::ElevatorStateVariant newState) const {
        auto newElevator = std::visit([this](auto&& statePtr) -> Elevator {
            if (statePtr == nullptr) {
                throw std::invalid_argument("Null pointer in ElevatorStateVariant");
            }
            using T = std::decay_t<decltype(*statePtr)>;

            if constexpr (std::is_base_of_v<states::DoorState, T>) {
                return Elevator(doorDelayMs_, moveDelayMs_, current_, operationState_, statePtr, heading_, pendingPassengers_, boardedPassengers_, onStateChange_);
            }
            else if constexpr (std::is_base_of_v<states::Heading, T>) {
                return Elevator(doorDelayMs_, moveDelayMs_, current_, operationState_, doorState_, statePtr, pendingPassengers_, boardedPassengers_, onStateChange_);
            }
            else if constexpr (std::is_base_of_v<states::OperationState, T>) {
                return Elevator(doorDelayMs_, moveDelayMs_, current_, statePtr, doorState_, heading_, pendingPassengers_, boardedPassengers_, onStateChange_);
            }
            else {
                throw std::logic_error("Unhandled Elevator state type");
            }
            }, newState);

        if (newElevator.onStateChange_) {
            core::events::StateChangeEvent<Elevator, states::ElevatorStateVariant> event(newElevator, newState);
            newElevator.onStateChange_(newState);
        }

        return newElevator;
    }

    Elevator Elevator::AddCallback(const core::event::StateChangeCallback<const core::event::StateChangeEvent<ElevatorStateVariant>&>& callback) const {
        return Elevator(doorDelayMs_, moveDelayMs_, current_, operationState_, doorState_, heading_, pendingPassengers_, boardedPassengers_, callback);
    }

    bool Elevator::IsIdle() const {
        return operationState_ == &states::ElevatorStates::Idle();
    }

    std::ostream& operator<<(std::ostream& os, const Elevator& elevator) {
        os << "Elevator at floor " << elevator.CurrentFloor()
            << ", OperationState: " << (elevator.IsIdle() ? "Idle" : "Active");
        return os;
    }

} // namespace elevator::models
