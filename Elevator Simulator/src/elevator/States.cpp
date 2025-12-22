// src/elevator/States.cpp
#include "States.h"
#include "detail/DoorsClosed.h"
#include "detail/DoorsClosing.h"
#include "detail/DoorsOpened.h"
#include "detail/DoorsOpening.h"
#include "detail/GoingDown.h"
#include "detail/GoingUp.h"
#include "detail/OperationActive.h"
#include "detail/OperationIdle.h"

namespace elevator {

	const DoorState& DOORS_CLOSED() {
		return detail::DoorsClosed::instance();
	}
	
	const DoorState& DOORS_CLOSING() {
		return detail::DoorsClosing::instance();
	}

	const DoorState& DOORS_OPENED() {
		return detail::DoorsOpened::instance();
	}

	const DoorState& DOORS_OPENING() {
		return detail::DoorsOpening::instance();
	}

	const Heading& GOING_DOWN() {
		return detail::GoingDown::instance();
	}

	const Heading& GOING_UP() {
		return detail::GoingUp::instance();
	}

	const OperationState& ACTIVE() {
		return detail::OperationActive::instance();
	}

	const OperationState& IDLE() {
		return detail::OperationIdle::instance();
	}
}