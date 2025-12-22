// elevator/States.h
#ifndef ELEVATOR_STATES_H
#define ELEVATOR_STATES_H
#include "Heading.h"
#include "DoorState.h"
#include "OperationState.h"
#include "core/Core.h"
namespace elevator {

    using core::operator==;
    using core::operator!=;
    using core::operator<=>;
    
    // Forward declare the implementation type in detail namespace
    namespace detail {
        using core::operator==;
        using core::operator!=;
        using core::operator<=>;

        struct DoorsClosed;
        struct DoorsClosing;
        struct DoorsOpened;
        struct DoorsOpening;

        struct DoorState;

        struct GoingDown;
        struct GoingUp;
        struct Stopped;

        struct Heading;

        struct OperationActive;
        struct OperationIdle;

        struct OperationState;
    }

    using DoorState = detail::DoorState;
    using Heading = detail::Heading;
    using OperationState = detail::OperationState;

    const DoorState& DOORS_CLOSED();
    const DoorState& DOORS_CLOSING();
    const DoorState& DOORS_OPENED();
    const DoorState& DOORS_OPENING();

    const Heading& GOING_DOWN();
    const Heading& GOING_UP();
    const Heading& STOPPED();

    const OperationState& ACTIVE();
    const OperationState& IDLE();

} // namespace elevator

#endif // ELEVATOR_STATES_H