// elevator/services/MovementService.h

#ifndef ELEVATOR_SERVICES_MOVEMENT_SERVICE_H
#define ELEVATOR_SERVICES_MOVEMENT_SERVICE_H

#include "elevator/models/Elevator.h"

namespace elevator::services {

    struct MovementService {
        // Move elevator one floor based on current heading and return new floor number
        static int MoveOneFloor(const Elevator& elevator);

        // Update elevator heading if needed (e.g., change direction at top/bottom floors)
        static Elevator UpdateHeadingIfNeeded(const Elevator& elevator);

        // Determine if elevator should idle (no passengers or no requests)
        static bool ShouldIdle(const Elevator& elevator);
    };

} //namespace elevator::services

#endif // ELEVATOR_SERVICES_MOVEMENT_SERVICE_H