// core/detail/StateChangeEvent.h
#ifndef CORE_DETAIL_STATE_CHANGE_EVENT_H
#define CORE_DETAIL_STATE_CHANGE_EVENT_H

#include <type_traits>
#include <stdexcept>

namespace core::detail {

    template <typename Category, typename State>
    struct StateChangeEvent {
        const Category* categoryInstance;
        const State* stateInstance;

        StateChangeEvent(const Category* category, const State* state)
            : categoryInstance(category), stateInstance(state)
        {
            if (!stateInstance) {
                throw std::invalid_argument("StateChangeEvent requires non-null stateInstance");
            }
        }

        template <typename T>
            requires std::is_base_of_v<State, T>
        const T* As() const {
            return dynamic_cast<const T*>(stateInstance);
        }
    };

} // namespace core::detail

#endif // CORE_DETAIL_STATE_CHANGE_EVENT_H
