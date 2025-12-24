// elevator/models/states/Variants.h

#ifndef ELEVATOR_MODELS_STATES_VARIANTS_H
#define ELEVATOR_MODELS_STATES_VARIANTS_H

// Concrete state includes
#include "elevator/models/states/details/Closed.h"
#include "elevator/models/states/details/Closing.h"
#include "elevator/models/states/details/Opened.h"
#include "elevator/models/states/details/Opening.h"
#include "elevator/models/states/details/GoingDown.h"
#include "elevator/models/states/details/GoingUp.h"
#include "elevator/models/states/details/Active.h"
#include "elevator/models/states/details/Idle.h"
#include "elevator/models/states/details/Stopped.h"

namespace elevator::model::states {

    // Category variants
    using DoorStateVariant = std::variant<
        const elevator::model::states::details::DoorsClosed*,
        const elevator::model::states::details::DoorsClosing*,
        const elevator::model::states::details::DoorsOpened*,
        const elevator::model::states::details::DoorsOpening*
    >;

    using HeadingVariant = std::variant<
        const elevator::model::states::details::GoingUp*,
        const elevator::model::states::details::GoingDown*,
        const elevator::model::states::details::Stopped*
    >;

    using OperationVariant = std::variant<
        const elevator::model::states::details::OperationActive*,
        const elevator::model::states::details::OperationIdle*
    >;

    using DomainStateVariant = std::variant<
        const elevator::model::states::details::DoorsClosed*,
        const elevator::model::states::details::DoorsClosing*,
        const elevator::model::states::details::DoorsOpened*,
        const elevator::model::states::details::DoorsOpening*,
        const elevator::model::states::details::GoingUp*,
        const elevator::model::states::details::GoingDown*,
        const elevator::model::states::details::Stopped*,
        const elevator::model::states::details::OperationActive*,
        const elevator::model::states::details::OperationIdle*
    >;
} // namespace elevator::model::states

#endif // ELEVATOR_MODELS_STATES_VARIANTS_H