// elevator/DomainEvent.h
#ifndef ELEVATOR_DOMAIN_EVENT_H
#define ELEVATOR_DOMAIN_EVENT_H

#include "core/Core.h"
#include "elevator/DomainRegistry.h"
#include "elevator/detail/DomainState.h"

namespace elevator {

    using DoorEvent = detail::DoorState;
    using HeadingEvent = detail::Heading;
    using OperationEvent = detail::OperationState;

    // Callbacks accept StateChangeEvent<Category> with polymorphic reference
    using DoorStateChangeCallback = core::detail::StateChangeCallback<const core::detail::StateChangeEvent<DoorEvent>&>;
    using HeadingStateChangeCallback = core::detail::StateChangeCallback<const core::detail::StateChangeEvent<HeadingEvent>&>;
    using OperationStateChangeCallback = core::detail::StateChangeCallback<const core::detail::StateChangeEvent<OperationEvent>&>;

} // namespace elevator

#endif // ELEVATOR_DOMAIN_EVENT_H
