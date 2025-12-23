// elevator/DomainEvent.h
#ifndef ELEVATOR_DOMAIN_EVENT_H
#define ELEVATOR_DOMAIN_EVENT_H

#include "core/Core.h"
#include "elevator/detail/Variants.h"

namespace elevator {

    struct DomainStateChangeEvent {
        DomainStateVariant state;
        explicit DomainStateChangeEvent(DomainStateVariant s) : state(std::move(s)) {}
    };

    struct DoorStateChangeEvent {
        DoorStateVariant state;
        explicit DoorStateChangeEvent(DoorStateVariant s) : state(std::move(s)) {}
    };

    struct HeadingStateChangeEvent {
        HeadingVariant state;
        explicit HeadingStateChangeEvent(HeadingVariant s) : state(std::move(s)) {}
    };

    struct OperationStateChangeEvent {
        OperationVariant state;
        explicit OperationStateChangeEvent(OperationVariant s) : state(std::move(s)) {}
    };

    // Callback aliases
    using DomainStateChangeCallback = core::StateChangeCallback<const DomainStateChangeEvent&>;
    using DoorStateChangeCallback = core::StateChangeCallback<const DoorStateChangeEvent&>;
    using HeadingStateChangeCallback = core::StateChangeCallback<const HeadingStateChangeEvent&>;
    using OperationStateChangeCallback = core::StateChangeCallback<const OperationStateChangeEvent&>;

} // namespace elevator

#endif // ELEVATOR_DOMAIN_EVENT_H
