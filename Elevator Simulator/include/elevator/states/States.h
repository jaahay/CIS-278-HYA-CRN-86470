// elevator/states/States.h
#ifndef ELEVATOR_STATES_STATES_H
#define ELEVATOR_STATES_STATES_H

#include "elevator/states/Types.h"

// Concrete state includes
#include "elevator/states/details/DoorsClosed.h"
#include "elevator/states/details/DoorsClosing.h"
#include "elevator/states/details/DoorsOpened.h"
#include "elevator/states/details/DoorsOpening.h"
#include "elevator/states/details/GoingDown.h"
#include "elevator/states/details/GoingUp.h"
#include "elevator/states/details/OperationActive.h"
#include "elevator/states/details/OperationIdle.h"
#include "elevator/states/details/Stopped.h"

namespace elevator::states {

    inline const elevator::states::DoorsClosed& DoorsClosed() {
        return states::details::DoorsClosed::instance();
    }
    inline const elevator::states::DoorsClosing& DoorsClosing() {
        return states::details::DoorsClosing::instance();
    }
    inline const elevator::states::DoorsOpened& DoorsOpened() {
        return states::details::DoorsOpened::instance();
    }
    inline const elevator::states::DoorsOpening& DoorsOpening() {
        return states::details::DoorsOpening::instance();
    }
    inline const elevator::states::GoingDown& GoingDown() {
        return states::details::GoingDown::instance();
    }
    inline const elevator::states::GoingUp& GoingUp() {
        return states::details::GoingUp::instance();
    }
    inline const elevator::states::Stopped& Stopped() {
        return states::details::Stopped::instance();
    }
    inline const elevator::states::OperationActive& Active() {
        return states::details::OperationActive::instance();
    }
    inline const elevator::states::OperationIdle& Idle() {
        return states::details::OperationIdle::instance();
    }

} // namespace elevator::states

#endif // ELEVATOR_STATES_STATES_H
