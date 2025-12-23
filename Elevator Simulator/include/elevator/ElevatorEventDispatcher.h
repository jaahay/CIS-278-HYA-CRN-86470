// elevator/ElevatorEventDispatcher.h
#ifndef ELEVATOR_ELEVATOR_EVENT_DISPATCHER_H
#define ELEVATOR_ELEVATOR_EVENT_DISPATCHER_H

#include "core/core.h"
#include "elevator/DomainRegistry.h"

namespace elevator {

    using DoorEventDispatcher = core::detail::StateEventDispatcher<DoorCategory>;
    using HeadingEventDispatcher = core::detail::StateEventDispatcher<HeadingCategory>;
    using OperationEventDispatcher = core::detail::StateEventDispatcher<OperationCategory>;

} // namespace elevator

#endif // ELEVATOR_ELEVATOR_EVENT_DISPATCHER_H
