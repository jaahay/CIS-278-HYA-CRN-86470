// elevator/states/ElevatorStateVariants.h
#ifndef ELEVATOR_STATES_ELEVATOR_STATE_VARIANTS_H
#define ELEVATOR_STATES_ELEVATOR_STATE_VARIANTS_H

#include <variant>

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
        const elevator::states::Closed*,
        const elevator::states::Closing*,
        const elevator::states::Opened*,
        const elevator::states::Opening*
    >;

    using HeadingVariant = std::variant<
        const elevator::states::GoingUp*,
        const elevator::states::GoingDown*,
        const elevator::states::Stopped*
    >;

    using OperationVariant = std::variant<
        const elevator::states::Active*,
        const elevator::states::Idle*
    >;

    using ElevatorStateVariant = std::variant<
        const elevator::states::Closed*,
        const elevator::states::Closing*,
        const elevator::states::Opened*,
        const elevator::states::Opening*,
        const elevator::states::GoingUp*,
        const elevator::states::GoingDown*,
        const elevator::states::Stopped*,
        const elevator::states::Active*,
        const elevator::states::Idle*
    >;
} // namespace elevator::states

#endif // ELEVATOR_STATES_ELEVATOR_STATE_VARIANTS_H