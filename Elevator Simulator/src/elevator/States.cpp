// src/elevator/States.cpp
#include "States.h"
#include "detail/OperationActive.h"

namespace elevator {
	const OperationActive& ACTIVE() {
		return detail::OperationActive::instance();
	}
}