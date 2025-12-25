// core/event/StateChangeEvent.h
#ifndef CORE_EVENT_STATE_CHANGE_EVENT_H
#define CORE_EVENT_STATE_CHANGE_EVENT_H

#include <stdexcept>

#include "core/concepts/Concepts.h"

namespace core::event {

    template <core::concepts::Abstract ObjectType, typename StateType>
        requires ValidStateType<StateType, ObjectType>
    struct StateChangeEvent {
        const ObjectType& objectInstance;
        const StateType& stateInstance; // polymorphic reference to concrete state  

        StateChangeEvent(const ObjectType& obj, const StateType& state)
            : objectInstance(obj), stateInstance(state) {
        }

        template <typename T>
        const T* As() const {
            return dynamic_cast<const T*>(&stateInstance);
        }
    };

    template<typename ObjectType, typename StateType, typename CallbackType>
        requires CallableWith<CallbackType, const StateChangeEvent<ObjectType, StateType>&>
    inline void NotifyStateChange(const ObjectType& obj, const StateType& state, const CallbackType& callback) {
        if (callback) {
            StateChangeEvent<ObjectType, StateType> event(obj, state);
            callback(event);
        }
    }

} // namespace core::event

#endif // CORE_EVENT_STATE_CHANGE_EVENT_H
