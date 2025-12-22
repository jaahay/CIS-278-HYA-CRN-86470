// include/core/BaseState.h
#ifndef CORE_BASE_STATE_H
#define CORE_BASE_STATE_H

#include <iostream>
#include <compare>

namespace core {

    struct BaseState {
        virtual ~BaseState() = default;

        virtual void print(std::ostream& os) const = 0;
        virtual bool equals(const BaseState& other) const = 0;
        virtual std::strong_ordering compare(const BaseState& other) const = 0;

        friend std::ostream& operator<<(std::ostream& os, const BaseState& state) {
            state.print(os);
            return os;
        }

        bool operator==(const BaseState& other) const {
            return equals(other);
        }

        auto operator<=>(const BaseState& other) const {
            return compare(other);
        }
    };

} // namespace core

#endif // CORE_BASE_STATE_H