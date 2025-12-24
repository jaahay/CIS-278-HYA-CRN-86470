// elevator/services/StateNotificationService.cpp
#include "elevator/services/StateNotificationService.h"

namespace elevator::services {

    template <typename StateVariant>
    void StateNotificationService::NotifyStateChange(const Elevator& elevator, const StateVariant& stateVariant) {
        // No need to check for nullptr if onStateChange_ is always valid (NoOpCallback)
        core::event::StateChangeEvent<Elevator, StateVariant> event(elevator, stateVariant);
        elevator.onStateChange_(event);
    }

    // Explicit instantiations (if needed)
    template void StateNotificationService::NotifyStateChange(const Elevator&, const elevator::states::DoorStateVariant&);
    template void StateNotificationService::NotifyStateChange(const Elevator&, const elevator::states::HeadingVariant&);
    template void StateNotificationService::NotifyStateChange(const Elevator&, const elevator::states::OperationVariant&);
    template void StateNotificationService::NotifyStateChange(const Elevator&, const elevator::states::ElevatorStateVariant&);

} // namespace elevator::services