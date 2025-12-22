#include "include/elevator/ElevatorStates.h"

namespace elevator::detail {
	const OperationActive& OperationActive_Instance() {
		return OperationActive::instance();
	}
}