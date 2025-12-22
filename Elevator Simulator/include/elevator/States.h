// include/elevator/States.h
#ifndef ELEVATOR_STATES_H
#define ELEVATOR_STATES_H

#include "core/BaseState.h"
namespace elevator {
    // Forward declare the implementation type in detail namespace
    namespace detail {
        struct OperationState;
        struct OperationActive;
    }

    // Public-facing alias or wrapper for OperationState
    using OperationState = detail::OperationState;
    using OperationActive = detail::OperationActive;

    const OperationActive& OperationActive_Instance();
    /*struct DoorState : TemplateState<DoorState> {};
    struct Heading : TemplateState<Heading> {};*/
} // namespace elevator

#endif // ELEVATOR_STATES_H