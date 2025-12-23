// elevator/DomainRegistry.h
#ifndef ELEVATOR_DOMAIN_REGISTRY_H
#define ELEVATOR_DOMAIN_REGISTRY_H

#include "elevator/detail/DomainState.h"
#include "elevator/detail/DoorsClosed.h"
#include "elevator/detail/DoorsClosing.h"
#include "elevator/detail/DoorsOpened.h"
#include "elevator/detail/DoorsOpening.h"
#include "elevator/detail/GoingDown.h"
#include "elevator/detail/GoingUp.h"
#include "elevator/detail/OperationActive.h"
#include "elevator/detail/OperationIdle.h"
#include "elevator/detail/Stopped.h"

#include <tuple>

namespace elevator {

    using DoorCategory = detail::DoorState;
    using HeadingCategory = detail::Heading;
    using OperationCategory = detail::OperationState;

    template <typename Category>
    struct StateRegistry;

    template <>
    struct StateRegistry<DoorCategory> {
        using Types = std::tuple<
            detail::DoorsClosed,
            detail::DoorsClosing,
            detail::DoorsOpened,
            detail::DoorsOpening
        >;
    };

    template <>
    struct StateRegistry<HeadingCategory> {
        using Types = std::tuple<
            detail::GoingUp,
            detail::GoingDown,
            detail::Stopped
        >;
    };

    template <>
    struct StateRegistry<OperationCategory> {
        using Types = std::tuple<
            detail::OperationActive,
            detail::OperationIdle
        >;
    };

} // namespace elevator

#endif // ELEVATOR_DOMAIN_REGISTRY_H
