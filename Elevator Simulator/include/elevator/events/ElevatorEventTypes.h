// elevator/events/ElevatorEventTypes.h
#ifndef ELEVATOR_EVENTS_ELEVATOR_EVENT_TYPES_H
#define ELEVATOR_EVENTS_ELEVATOR_EVENT_TYPES_H

#include "core/Core.h"
#include "elevator/detail/ElevatorStateVariants.h"

namespace elevator::events {

    struct ElevatorStateChangeEvent {
        ElevatorStateVariant state;
        explicit ElevatorStateChangeEvent(ElevatorStateVariant s) : state(std::move(s)) {}
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

    // Forward NotifyStateChange from core detail namespace
    template<typename ObjectType, typename StateType, typename CallbackType>
    inline void NotifyStateChange(const ObjectType& obj, const StateType& state, const CallbackType& callback) {
        core::detail::NotifyStateChange(obj, state, callback);
    }

    // Callback aliases
    using ElevatorStateChangeCallback = core::StateChangeCallback<const ElevatorStateChangeEvent&>;
    using DoorStateChangeCallback = core::StateChangeCallback<const DoorStateChangeEvent&>;
    using HeadingStateChangeCallback = core::StateChangeCallback<const HeadingStateChangeEvent&>;
    using OperationStateChangeCallback = core::StateChangeCallback<const OperationStateChangeEvent&>;

} // namespace elevator::events

#endif // ELEVATOR_EVENTS_ELEVATOR_EVENT_TYPES_H
