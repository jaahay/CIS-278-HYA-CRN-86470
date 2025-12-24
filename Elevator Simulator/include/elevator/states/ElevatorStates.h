// elevator/states/ElevatorStates.h
#ifndef ELEVATOR_STATES_ELEVATOR_STATES_H
#define ELEVATOR_STATES_ELEVATOR_STATES_H

#include "elevator/states/ElevatorStateTypes.h"

// Concrete state includes
#include "elevator/states/Closed.h"
#include "elevator/states/Closing.h"
#include "elevator/states/Opened.h"
#include "elevator/states/Opening.h"
#include "elevator/states/GoingDown.h"
#include "elevator/states/GoingUp.h"
#include "elevator/states/Active.h"
#include "elevator/states/Idle.h"
#include "elevator/states/Stopped.h"

namespace elevator::states {

    inline const elevator::states::DoorsClosed& DoorsClosed() {
        returnelevator::states::DoorsClosed::instance();
    }
    inline const elevator::states::DoorsClosing& DoorsClosing() {
        returnelevator::states::DoorsClosing::instance();
    }
    inline const elevator::states::DoorsOpened& DoorsOpened() {
        returnelevator::states::DoorsOpened::instance();
    }
    inline const elevator::states::DoorsOpening& DoorsOpening() {
        returnelevator::states::DoorsOpening::instance();
    }
    inline const elevator::states::GoingDown& GoingDown() {
        returnelevator::states::GoingDown::instance();
    }
    inline const elevator::states::GoingUp& GoingUp() {
        returnelevator::states::GoingUp::instance();
    }
    inline const elevator::states::Stopped& Stopped() {
        returnelevator::states::Stopped::instance();
    }
    inline const elevator::states::OperationActive& Active() {
        returnelevator::states::OperationActive::instance();
    }
    inline const elevator::states::OperationIdle& Idle() {
        returnelevator::states::OperationIdle::instance();
    }

} // namespace elevator::states

#endif // ELEVATOR_STATES_ELEVATOR_STATES_H
