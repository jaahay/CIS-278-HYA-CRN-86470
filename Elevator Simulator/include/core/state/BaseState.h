// core/state/BaseState.h
#ifndef CORE_STATE_BASE_STATE_H
#define CORE_STATE_BASE_STATE_H

#include <iostream>
#include <compare>

namespace core::state {

    struct BaseState {
        virtual ~BaseState() = default;

        virtual bool equals(const BaseState& other) const = 0;
        virtual std::strong_ordering compare(const BaseState& other) const = 0;

        bool operator==(const BaseState& other) const {
            return equals(other);
        }

        auto operator<=>(const BaseState& other) const {
            return compare(other);
        }

        virtual void print(std::ostream& os) const = 0;

        friend std::ostream& operator<<(std::ostream& os, const BaseState& state) {
            state.print(os);
            return os;
        }
    };

    template <typename StateType>
        requires std::is_base_of_v<BaseState, StateType>
    inline bool operator==(const StateType& lhs, const StateType& rhs) {
        return static_cast<const BaseState&>(lhs) == static_cast<const BaseState&>(rhs);
    }

    template <typename StateType>
        requires std::is_base_of_v<BaseState, StateType>
    inline bool operator!=(const StateType& lhs, const StateType& rhs) {
        return !(lhs == rhs);
    }

    template <typename StateType>
        requires std::is_base_of_v<BaseState, StateType>
    inline std::strong_ordering operator<=>(const StateType& lhs, const StateType& rhs) {
        return static_cast<const BaseState&>(lhs) <=> static_cast<const BaseState&>(rhs);
    }

} // namespace core::state

#endif // CORE_STATE_BASE_STATE_H
