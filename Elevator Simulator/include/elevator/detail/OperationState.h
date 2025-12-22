#ifndef ELEVATOR_DETAIL_OPERATION_STATE_H
#define ELEVATOR_DETAIL_OPERATION_STATE_H

#include "core/Core.h"
#include <compare>

namespace elevator::detail {

    struct OperationState : core::BaseState {
        virtual ~OperationState() = default;
        void print(std::ostream& os) const override = 0;
    };

    // Non-member comparison operators for OperationState
    inline bool operator==(const OperationState& lhs, const OperationState& rhs) {
        return static_cast<const core::BaseState&>(lhs) == static_cast<const core::BaseState&>(rhs);
    }

    inline bool operator!=(const OperationState& lhs, const OperationState& rhs) {
        return !(lhs == rhs);
    }

    inline std::strong_ordering operator<=>(const OperationState& lhs, const OperationState& rhs) {
        return static_cast<const core::BaseState&>(lhs) <=> static_cast<const core::BaseState&>(rhs);
    }

} // namespace elevator::detail

#endif // ELEVATOR_DETAIL_OPERATION_STATE_H
