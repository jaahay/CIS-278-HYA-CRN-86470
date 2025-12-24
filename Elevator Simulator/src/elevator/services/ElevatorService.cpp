// elevator/services/ElevatorService.cpp
#include "elevator/services/ElevatorService.h"
#include "elevator/services/PassengerService.h"
#include "elevator/services/MovementService.h"
#include "elevator/services/DoorService.h"
#include "elevator/services/StateNotificationService.h"
#include "elevator/states/ElevatorStates.h"
#include <iostream>
#include <algorithm>

namespace elevator::services {

    ElevatorService::ElevatorService()
        : elevator_()
        , busy_(false)
    {
    }

    std::future<Elevator> ElevatorService::AddPassenger(const Passenger passenger) {
        return std::async(std::launch::async, [this, passenger]() {
            std::lock_guard lock(mutex_);

            // Access private member via friendship
            const auto& pending = elevator_.pendingPassengers_;

            if (std::find(pending.begin(), pending.end(), &passenger) == pending.end()) {
                std::list<const Passenger*> newPending = pending;
                newPending.push_back(&passenger);

                Elevator updatedElevator(
                    elevator_.doorDelayMs_,
                    elevator_.moveDelayMs_,
                    elevator_.current_,
                    &states::ElevatorStates::Active(),
                    elevator_.doorState_,
                    elevator_.heading_,
                    std::move(newPending),
                    elevator_.boardedPassengers_,
                    elevator_.onStateChange_
                );

                UpdateElevatorState(updatedElevator);
            }

            Elevator movedElevator = PerformMoveStep();
            UpdateElevatorState(movedElevator);

            dispatcher_.Notify(elevator_, ElevatorStateVariant(&states::ElevatorStates::Active()));

            return elevator_;
            });
    }

    std::future<Elevator> ElevatorService::Move() {
        return std::async(std::launch::async, [this]() {
            std::lock_guard lock(mutex_);
            Elevator movedElevator = PerformMoveStep();
            UpdateElevatorState(movedElevator);
            return elevator_;
            });
    }

    void ElevatorService::Wait(std::chrono::milliseconds timeout) {
        std::unique_lock lock(mutex_);
        cv_.wait_for(lock, timeout, [this]() { return !busy_.load() || elevator_.IsIdle(); });
    }

    Elevator ElevatorService::GetElevator() const {
        std::lock_guard lock(mutex_);
        return elevator_;
    }

    ObserverId ElevatorService::AddObserver(core::StateChangeCallback<const core::detail::StateChangeEvent<ElevatorStateVariant>&> observer) {
        return dispatcher_.AddObserver(std::move(observer));
    }

    bool ElevatorService::RemoveObserver(ObserverId id) {
        return dispatcher_.RemoveObserver(id);
    }

    Elevator ElevatorService::PerformMoveStep() {
        Elevator updated = elevator_;

        // Board passengers
        updated = services::PassengerService::BoardPassengers(updated);

        // Passengers leave
        updated = services::PassengerService::PassengersLeave(updated);

        // Determine next door state and transition
        const states::DoorState* newDoorState = services::DoorService::DetermineNextDoorState(updated);
        if (newDoorState != updated.GetDoorState()) {
            updated = updated.Transition(ElevatorStateVariant(newDoorState));
            services::StateNotificationService::NotifyStateChange(updated, newDoorState);
        }

        // Determine next heading and transition
        const states::Heading* newHeading = services::MovementService::DetermineNextHeading(updated);
        if (newHeading != updated.GetHeading()) {
            updated = updated.Transition(ElevatorStateVariant(newHeading));
            services::StateNotificationService::NotifyStateChange(updated, newHeading);
        }

        // Move one floor if needed and create new state
        int newFloor = services::MovementService::CalculateNextFloor(updated);
        if (newFloor != updated.CurrentFloor()) {
            updated = Elevator(
                updated.doorDelayMs_,
                updated.moveDelayMs_,
                newFloor,
                updated.GetOperationState(),
                updated.GetDoorState(),
                updated.GetHeading(),
                updated.GetPendingPassengers(),
                updated.GetBoardedPassengers(),
                updated.onStateChange_
            );

            services::StateNotificationService::NotifyStateChange(updated, newFloor);
            std::cout << "Elevator moved to floor " << newFloor << std::endl;
        }

        return updated;
    }

    void ElevatorService::UpdateElevatorState(const Elevator& newElevator) {
        {
            std::lock_guard lock(mutex_);
            elevator_ = newElevator;
        }
        cv_.notify_all();
    }

} // namespace elevator::services
