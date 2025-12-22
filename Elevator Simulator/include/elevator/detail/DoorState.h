// include/elevator/detail/DoorState.h
#ifndef ELEVATOR_DETAIL_DOOR_STATE_H
#define ELEVATOR_DETAIL_DOOR_STATE_H

#include "core/BaseState.h"

namespace elevator::detail {

    struct DoorState : core::BaseState {
        virtual ~DoorState() = default;

        bool equals(const BaseState& other) const override {
            if (typeid(*this) != typeid(other)) return false;
            return this == &other;
        }

        std::strong_ordering compare(const BaseState& other) const override {
            if (typeid(*this) != typeid(other)) {
                return std::string_view(typeid(*this).name()) <=> std::string_view(typeid(other).name());
            }
            if (this == &other) return std::strong_ordering::equal;
            return this < &other ? std::strong_ordering::less : std::strong_ordering::greater;
        }

        void print(std::ostream& os) const override = 0;
    };

} // namespace elevator::detail

#endif // ELEVATOR_DETAIL_DOOR_STATE_H
