// include/elevator/detail/DomainStates.h
#ifndef ELEVATOR_DETAIL_DOMAINSTATES_H
#define ELEVATOR_DETAIL_DOMAINSTATES_H

#include "BaseState.h"

namespace elevator::detail {

    struct DirectionState : BaseState {
        // Add direction-specific virtual methods here if needed
    };

    struct OperationState : BaseState {
        // Add operation-specific virtual methods here if needed
    };

} // namespace elevator::detail

#endif // ELEVATOR_DETAIL_DOMAINSTATES_H