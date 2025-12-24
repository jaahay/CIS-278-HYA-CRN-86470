// elevator/models/states/details/Registry.h
#ifndef ELEVATOR_MODELS_STATES_DETAILS_REGISTRY_H
#define ELEVATOR_MODELS_STATES_DETAILS_REGISTRY_H

#include "elevator/models/states/details/DomainState.h"
#include "elevator/models/states/details/DoorsClosed.h"
#include "elevator/models/states/details/DoorsClosing.h"
#include "elevator/models/states/details/DoorsOpened.h"
#include "elevator/models/states/details/DoorsOpening.h"
#include "elevator/models/states/details/GoingDown.h"
#include "elevator/models/states/details/GoingUp.h"
#include "elevator/models/states/details/OperationActive.h"
#include "elevator/models/states/details/OperationIdle.h"
#include "elevator/models/states/details/Stopped.h"

#include <tuple>

namespace elevator::model::states::details {

    using DoorCategory = elevator::model::states::details::DoorState;
    using HeadingCategory = elevator::model::states::details::Heading;
    using OperationCategory = elevator::model::states::details::OperationState;

    template <typename Category>
    struct StateRegistry;

    template <>
    struct StateRegistry<DoorCategory> {
        using Types = std::tuple<
            elevator::model::states::details::Closed,
            elevator::model::states::details::Closing,
            elevator::model::states::details::Opened,
            elevator::model::states::details::Opening
        >;
    };

    template <>
    struct StateRegistry<HeadingCategory> {
        using Types = std::tuple<
            elevator::model::states::details::GoingUp,
            elevator::model::states::details::GoingDown,
            elevator::model::states::details::Stopped
        >;
    };

    template <>
    struct StateRegistry<OperationCategory> {
        using Types = std::tuple<
            elevator::model::states::details::Active,
            elevator::model::states::details::Idle
        >;
    };

} // namespace elevator::model::states::details

#endif // ELEVATOR_MODELS_STATES_DETAILS_REGISTRY_H
