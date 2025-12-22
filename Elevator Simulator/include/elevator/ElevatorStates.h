// include/elevator/ElevatorStates.h
#ifndef ELEVATOR_STATES_H
#define ELEVATOR_STATES_H
#include "detail/BaseState.h"
namespace elevator::detail {
    struct OperationState;
    struct OperationActive;
    const OperationActive& OperationActive_Instance();
    /*struct DoorState : TemplateState<DoorState> {};
    struct Heading : TemplateState<Heading> {};*/
} // namespace elevator

#endif // ELEVATOR_STATES_H