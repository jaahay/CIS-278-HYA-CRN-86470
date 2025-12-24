// elevator/states/ElevatorStateVariants.h
#ifndef ELEVATOR_STATES_ELEVATOR_STATE_VARIANTS_H
#define ELEVATOR_STATES_ELEVATOR_STATE_VARIANTS_H

// Concrete state includes
#include "elevator/states/Closed.h"
#include "elevator/states/Closing.h"
#include "elevator/states/Opened.h"
#include "elevator/states/Opening.h"
#include "elevator/states/GoingDown.h"
#include "elevator/states/GoingUp.h"
#include "elevator/states/Active.h"
#include "elevator/states/Idle.h"
#include "elevator/states/Stopped.h"

namespace elevator::states {

    // Category variants
    using DoorStateVariant = std::variant<
        const elevator::states::DoorsClosed*,
        const elevator::states::DoorsClosing*,
        const elevator::states::DoorsOpened*,
        const elevator::states::DoorsOpening*
    >;

    using HeadingVariant = std::variant<
        const elevator::states::GoingUp*,
        const elevator::states::GoingDown*,
        const elevator::states::Stopped*
    >;

    using OperationVariant = std::variant<
        const elevator::states::OperationActive*,
        const elevator::states::OperationIdle*
    >;

    using ElevatorStateVariant = std::variant<
        const elevator::states::DoorsClosed*,
        const elevator::states::DoorsClosing*,
        const elevator::states::DoorsOpened*,
        const elevator::states::DoorsOpening*,
        const elevator::states::GoingUp*,
        const elevator::states::GoingDown*,
        const elevator::states::Stopped*,
        const elevator::states::OperationActive*,
        const elevator::states::OperationIdle*
    >;
} // namespace elevator::states

#endif // ELEVATOR_STATES_ELEVATOR_STATE_VARIANTS_H