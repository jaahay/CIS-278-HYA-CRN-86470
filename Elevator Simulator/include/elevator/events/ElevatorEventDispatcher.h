// elevator/events/ElevatorEventDispatcher.h
#ifndef ELEVATOR_EVENTS_ELEVATOR_EVENT_DISPATCHER_H
#define ELEVATOR_EVENTS_ELEVATOR_EVENT_DISPATCHER_H

#include "core/Core.h"
#include "elevator/ElevatorEvent.h"

namespace elevator {

    using ElevatorEventDispatcher = core::detail::EventDispatcher<ElevatorStateChangeEvent>;
    using DoorEventDispatcher = core::detail::EventDispatcher<DoorStateChangeEvent>;
    using HeadingEventDispatcher = core::detail::EventDispatcher<HeadingStateChangeEvent>;
    using OperationEventDispatcher = core::detail::EventDispatcher<OperationStateChangeEvent>;

} // namespace elevator

#endif // ELEVATOR_EVENTS_ELEVATOR_EVENT_DISPATCHER_H