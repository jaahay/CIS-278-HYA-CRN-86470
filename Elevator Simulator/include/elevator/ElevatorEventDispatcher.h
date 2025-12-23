// elevator/ElevatorEventDispatcher.h
#ifndef ELEVATOR_ELEVATOR_EVENT_DISPATCHER_H
#define ELEVATOR_ELEVATOR_EVENT_DISPATCHER_H

#include "core/Core.h"
#include "elevator/DomainEvent.h"

namespace elevator {

    using DomainEventDispatcher = core::detail::EventDispatcher<DomainStateChangeEvent>;
    using DoorEventDispatcher = core::detail::EventDispatcher<DoorStateChangeEvent>;
    using HeadingEventDispatcher = core::detail::EventDispatcher<HeadingStateChangeEvent>;
    using OperationEventDispatcher = core::detail::EventDispatcher<OperationStateChangeEvent>;

} // namespace elevator

#endif // ELEVATOR_ELEVATOR_EVENT_DISPATCHER_H