// elevator/states/ElevatorStateTypes.h
#ifndef ELEVATOR_STATES_ELEVATOR_STATE_TYPES_H
#define ELEVATOR_STATES_ELEVATOR_STATE_TYPES_H

#include "core/Core.h"
#include <compare>
#include <ostream>

namespace elevator::states {

    struct DoorState : core::BaseState {
        virtual ~DoorState() = default;
        virtual bool IsOpened() const = 0;
        virtual bool IsClosed() const = 0;
        void print(std::ostream& os) const override = 0;
    };

    inline bool operator==(const DoorState& lhs, const DoorState& rhs) {
        return static_cast<const core::BaseState&>(lhs) == static_cast<const core::BaseState&>(rhs);
    }
    inline bool operator!=(const DoorState& lhs, const DoorState& rhs) {
        return !(lhs == rhs);
    }
    inline std::strong_ordering operator<=>(const DoorState& lhs, const DoorState& rhs) {
        return static_cast<const core::BaseState&>(lhs) <=> static_cast<const core::BaseState&>(rhs);
    }

    struct Heading : core::BaseState {
        virtual ~Heading() = default;
        virtual bool IsStopped() const = 0;
        virtual bool IsGoingUp() const = 0;
        virtual bool IsGoingDown() const = 0;
        void print(std::ostream& os) const override = 0;
    };

    inline bool operator==(const Heading& lhs, const Heading& rhs) {
        return static_cast<const core::BaseState&>(lhs) == static_cast<const core::BaseState&>(rhs);
    }
    inline bool operator!=(const Heading& lhs, const Heading& rhs) {
        return !(lhs == rhs);
    }
    inline std::strong_ordering operator<=>(const Heading& lhs, const Heading& rhs) {
        return static_cast<const core::BaseState&>(lhs) <=> static_cast<const core::BaseState&>(rhs);
    }

    struct OperationState : core::BaseState {
        virtual ~OperationState() = default;
        virtual bool IsActive() const = 0;
        void print(std::ostream& os) const override = 0;
    };

    inline bool operator==(const OperationState& lhs, const OperationState& rhs) {
        return static_cast<const core::BaseState&>(lhs) == static_cast<const core::BaseState&>(rhs);
    }
    inline bool operator!=(const OperationState& lhs, const OperationState& rhs) {
        return !(lhs == rhs);
    }
    inline std::strong_ordering operator<=>(const OperationState& lhs, const OperationState& rhs) {
        return static_cast<const core::BaseState&>(lhs) <=> static_cast<const core::BaseState&>(rhs);
    }

} // namespace elevator::states

#endif // ELEVATOR_STATES_ELEVATOR_STATE_TYPES_H
