#ifndef ELEVATOR_DETAIL_HEADING_H
#define ELEVATOR_DETAIL_HEADING_H

#include "core/Core.h"
#include <compare>

namespace elevator::detail {

    struct Heading : core::BaseState {
        virtual ~Heading() = default;
        void print(std::ostream& os) const override = 0;
    };

    // Non-member comparison operators for Heading
    inline bool operator==(const Heading& lhs, const Heading& rhs) {
        return static_cast<const core::BaseState&>(lhs) == static_cast<const core::BaseState&>(rhs);
    }

    inline bool operator!=(const Heading& lhs, const Heading& rhs) {
        return !(lhs == rhs);
    }

    inline std::strong_ordering operator<=>(const Heading& lhs, const Heading& rhs) {
        return static_cast<const core::BaseState&>(lhs) <=> static_cast<const core::BaseState&>(rhs);
    }

} // namespace elevator::detail

#endif // ELEVATOR_DETAIL_HEADING_H
