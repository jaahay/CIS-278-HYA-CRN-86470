// src/elevator/States.cpp
#include "States.h"
#include "detail/OperationActive.h"

namespace elevator {
	const OperationActive& OperationActive_Instance() {
		return detail::OperationActive::instance();
	}
}