#ifndef ELEVATOR_DETAIL_HEADING_H
#define ELEVATOR_DETAIL_HEADING_H

#include "core/Core.h"
#include <compare>
#include <Elevator.h>

namespace elevator::detail {

    struct Heading : core::BaseState {
        virtual ~Heading() = default;
        virtual bool IsStopped() const = 0;
        virtual bool IsGoingUp() const = 0;
        virtual bool IsGoingDown() const = 0;
        virtual bool PassedOrigin(const Elevator&, const Passenger&) const = 0;
        virtual bool PassedDestination(const Elevator&, const Passenger&) const = 0;
        bool GoingMyWay(const Passenger& passenger) const { return passenger.GoingMyWay(this); }
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
