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

    inline const states::Closed& Closed() {
        return elevator::states::Closed::instance();
    }
    inline const states::Closing& Closing() {
        return elevator::states::Closing::instance();
    }
    inline const states::Opened& Opened() {
        return elevator::states::Opened::instance();
    }
    inline const states::Opening& Opening() {
        return elevator::states::Opening::instance();
    }
    inline const states::GoingDown& GoingDown() {
        return elevator::states::GoingDown::instance();
    }
    inline const elevator::states::GoingUp& GoingUp() {
        return elevator::states::GoingUp::instance();
    }
    inline const elevator::states::Stopped& Stopped() {
        return elevator::states::Stopped::instance();
    }
    inline const elevator::states::Active& Active() {
        return elevator::states::Active::instance();
    }
    inline const elevator::states::Idle& Idle() {
        return elevator::states::Idle::instance();
    }

} // namespace elevator::states

#endif // ELEVATOR_STATES_ELEVATOR_STATES_H
