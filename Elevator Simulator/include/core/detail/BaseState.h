// core/detail/BaseState.h
#ifndef CORE_DETAIL_BASE_STATE_H
#define CORE_DETAIL_BASE_STATE_H

#include <iostream>
#include <compare>

namespace core::detail {

    struct BaseState {
        virtual ~BaseState() = default;

        // Polymorphic interface for equality and ordering
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

    // Template non-member operators for all BaseState-derived types
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

} // namespace core::detail

#endif // CORE_DETAIL_BASE_STATE_H
