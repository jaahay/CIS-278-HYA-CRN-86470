// include/elevator/States.h
#ifndef ELEVATOR_STATES_H
#define ELEVATOR_STATES_H

namespace elevator {
    
    // Forward declare the implementation type in detail namespace
    namespace detail {
        struct OperationState;
        struct OperationActive;
    }

    using OperationState = detail::OperationState;
    using OperationActive = detail::OperationActive;
    const OperationActive& ACTIVE();




} // namespace elevator

#endif // ELEVATOR_STATES_H