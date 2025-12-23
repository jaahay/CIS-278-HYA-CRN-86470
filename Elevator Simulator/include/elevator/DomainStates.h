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

    inline const elevator::detail::DoorState& DoorsClosed() {
        return detail::DoorsClosed::instance();
    }
    inline const elevator::detail::DoorState& DoorsClosing() {
        return detail::DoorsClosing::instance();
    }
    inline const elevator::detail::DoorState& DoorsOpened() {
        return detail::DoorsOpened::instance();
    }
    inline const elevator::detail::DoorState& DoorsOpening() {
        return detail::DoorsOpening::instance();
    }
    inline const elevator::detail::Heading& GoingDown() {
        return detail::GoingDown::instance();
    }
    inline const elevator::detail::Heading& GoingUp() {
        return detail::GoingUp::instance();
    }
    inline const elevator::detail::Heading& Stopped() {
        return detail::Stopped::instance();
    }
    inline const elevator::detail::OperationState& Active() {
        return detail::OperationActive::instance();
    }
    inline const elevator::detail::OperationState& Idle() {
        return detail::OperationIdle::instance();
    }

} // namespace elevator::DomainStates

#endif // ELEVATOR_DOMAIN_STATES_H
