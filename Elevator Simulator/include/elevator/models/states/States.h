// elevator/models/states/States.h
#ifndef ELEVATOR_MODELS_STATES_STATES_H
#define ELEVATOR_MODELS_STATES_STATES_H

#include "elevator/models/states/details/Types.h"

// Concrete state includes
#include "elevator/models/states/details/Closed.h"
#include "elevator/models/states/details/Closing.h"
#include "elevator/models/states/details/Opened.h"
#include "elevator/models/states/details/Opening.h"
#include "elevator/models/states/details/GoingDown.h"
#include "elevator/models/states/details/GoingUp.h"
#include "elevator/models/states/details/Active.h"
#include "elevator/models/states/details/Idle.h"
#include "elevator/models/states/details/Stopped.h"

namespace elevator::model::states {

    inline const elevator::model::states::DoorsClosed& DoorsClosed() {
        return states::details::DoorsClosed::instance();
    }
    inline const elevator::model::states::DoorsClosing& DoorsClosing() {
        return states::details::DoorsClosing::instance();
    }
    inline const elevator::model::states::DoorsOpened& DoorsOpened() {
        return states::details::DoorsOpened::instance();
    }
    inline const elevator::model::states::DoorsOpening& DoorsOpening() {
        return states::details::DoorsOpening::instance();
    }
    inline const elevator::model::states::GoingDown& GoingDown() {
        return states::details::GoingDown::instance();
    }
    inline const elevator::model::states::GoingUp& GoingUp() {
        return states::details::GoingUp::instance();
    }
    inline const elevator::model::states::Stopped& Stopped() {
        return states::details::Stopped::instance();
    }
    inline const elevator::model::states::OperationActive& Active() {
        return states::details::OperationActive::instance();
    }
    inline const elevator::model::states::OperationIdle& Idle() {
        return states::details::OperationIdle::instance();
    }

} // namespace elevator::model::states

#endif // ELEVATOR_MODELS_STATES_STATES_H
