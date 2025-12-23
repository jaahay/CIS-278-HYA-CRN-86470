// elevator/DomainStates.h
#ifndef ELEVATOR_DOMAIN_STATES_H
#define ELEVATOR_DOMAIN_STATES_H

#include "elevator/detail/DomainState.h"

// Concrete state includes
#include "elevator/detail/DoorsClosed.h"
#include "elevator/detail/DoorsClosing.h"
#include "elevator/detail/DoorsOpened.h"
#include "elevator/detail/DoorsOpening.h"
#include "elevator/detail/GoingDown.h"
#include "elevator/detail/GoingUp.h"
#include "elevator/detail/OperationActive.h"
#include "elevator/detail/OperationIdle.h"
#include "elevator/detail/Stopped.h"

namespace elevator::DomainStates {

    inline const elevator::detail::DoorsClosed& DoorsClosed() {
        return detail::DoorsClosed::instance();
    }
    inline const elevator::detail::DoorsClosing& DoorsClosing() {
        return detail::DoorsClosing::instance();
    }
    inline const elevator::detail::DoorsOpened& DoorsOpened() {
        return detail::DoorsOpened::instance();
    }
    inline const elevator::detail::DoorsOpening& DoorsOpening() {
        return detail::DoorsOpening::instance();
    }
    inline const elevator::detail::GoingDown& GoingDown() {
        return detail::GoingDown::instance();
    }
    inline const elevator::detail::GoingUp& GoingUp() {
        return detail::GoingUp::instance();
    }
    inline const elevator::detail::Stopped& Stopped() {
        return detail::Stopped::instance();
    }
    inline const elevator::detail::OperationActive& Active() {
        return detail::OperationActive::instance();
    }
    inline const elevator::detail::OperationIdle& Idle() {
        return detail::OperationIdle::instance();
    }

} // namespace elevator::DomainStates

#endif // ELEVATOR_DOMAIN_STATES_H
