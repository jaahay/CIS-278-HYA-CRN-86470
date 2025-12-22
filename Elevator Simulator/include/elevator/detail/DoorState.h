#ifndef ELEVATOR_DETAIL_DOOR_STATE_H
#define ELEVATOR_DETAIL_DOOR_STATE_H

#include "core/Core.h"
#include <compare>

namespace elevator::detail {

    struct DoorState : core::BaseState {
        virtual ~DoorState() = default;
        virtual bool Opened() const = 0;
        virtual bool Closed() const = 0;
        void print(std::ostream& os) const override = 0;
    };

    // Non-member comparison operators for DoorState
    inline bool operator==(const DoorState& lhs, const DoorState& rhs) {
        return static_cast<const core::BaseState&>(lhs) == static_cast<const core::BaseState&>(rhs);
    }

    inline bool operator!=(const DoorState& lhs, const DoorState& rhs) {
        return !(lhs == rhs);
    }

    inline std::strong_ordering operator<=>(const DoorState& lhs, const DoorState& rhs) {
        return static_cast<const core::BaseState&>(lhs) <=> static_cast<const core::BaseState&>(rhs);
    }

} // namespace elevator::detail

#endif // ELEVATOR_DETAIL_DOOR_STATE_H
