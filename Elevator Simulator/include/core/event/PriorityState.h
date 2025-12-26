// core/event/PriorityState.h
#ifndef CORE_EVENT_PRIORITY_STATE_H
#define CORE_EVENT_PRIORITY_STATE_H

#include "core/state/BaseState.h"

namespace core::event {

    // Marker base class for priority states
    struct PriorityState : core::state::BaseState {
        virtual ~PriorityState() = default;
    };

} // namespace core::event

#endif // CORE_EVENT_PRIORITY_STATE_H
