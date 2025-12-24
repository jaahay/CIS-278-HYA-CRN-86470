// core/event/StateChangeEvent.h
#ifndef CORE_EVENT_STATE_CHANGE_EVENT_H
#define CORE_EVENT_STATE_CHANGE_EVENT_H

#include <stdexcept>

namespace core::event {

    template <typename Category>
    struct StateChangeEvent {
        const Category& stateInstance;  // polymorphic reference to concrete state

        explicit StateChangeEvent(const Category& state)
            : stateInstance(state)
        {
        }

        template <typename T>
        const T* As() const {
            return dynamic_cast<const T*>(&stateInstance);
        }
    };

} // namespace core::event

#endif // CORE_EVENT_STATE_CHANGE_EVENT_H
