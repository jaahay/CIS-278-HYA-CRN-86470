// include/elevator/States.h
#ifndef ELEVATOR_STATES_H
#define ELEVATOR_STATES_H

namespace elevator {
    
    // Forward declare the implementation type in detail namespace
    namespace detail {
        struct DoorsClosed;
        struct DoorsClosing;
        struct DoorsOpened;
        struct DoorsOpening;
        struct DoorState;
        struct GoingDown;
        struct GoingUp;
        struct Heading;
        struct OperationActive;
        struct OperationIdle;
        struct OperationState;
    }

    using DoorState = detail::DoorState;
    const DoorState& DOORS_CLOSED();
    const DoorState& DOORS_CLOSING();
    const DoorState& DOORS_OPENED();
    const DoorState& DOORS_OPENING();

    using Heading = detail::Heading;
    const Heading& GOING_DOWN();
    const Heading& GOING_UP();

    using OperationState = detail::OperationState;
    const OperationState& ACTIVE();
    const OperationState& IDLE();




} // namespace elevator

#endif // ELEVATOR_STATES_H