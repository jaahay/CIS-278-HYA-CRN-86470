// elevator/states/ElevatorStateRegistry.h
#ifndef ELEVATOR_STATES_ELEVATOR_STATE_REGISTRY_REGISTRY_H
#define ELEVATOR_STATES_ELEVATOR_STATE_REGISTRY_REGISTRY_H

#include "elevator/states/ElevatorStateTypes.h"

#include "elevator/states/DoorsClosed.h"
#include "elevator/states/DoorsClosing.h"
#include "elevator/states/DoorsOpened.h"
#include "elevator/states/DoorsOpening.h"
#include "elevator/states/GoingDown.h"
#include "elevator/states/GoingUp.h"
#include "elevator/states/OperationActive.h"
#include "elevator/states/OperationIdle.h"
#include "elevator/states/Stopped.h"

#include <tuple>

namespace elevator::states {

    using DoorCategory = elevator::states::DoorState;
    using HeadingCategory = elevator::states::Heading;
    using OperationCategory = elevator::states::OperationState;

    template <typename Category>
    struct StateRegistry;

    template <>
    struct StateRegistry<DoorCategory> {
        using Types = std::tuple<
            elevator::states::Closed,
            elevator::states::Closing,
            elevator::states::Opened,
            elevator::states::Opening
        >;
    };

    template <>
    struct StateRegistry<HeadingCategory> {
        using Types = std::tuple<
            elevator::states::GoingUp,
            elevator::states::GoingDown,
            elevator::states::Stopped
        >;
    };

    template <>
    struct StateRegistry<OperationCategory> {
        using Types = std::tuple<
            elevator::states::Active,
            elevator::states::Idle
        >;
    };

} // namespace elevator::states

#endif // ELEVATOR_STATES_ELEVATOR_STATE_REGISTRY_REGISTRY_H
