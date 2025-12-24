// elevator/services/StateNotificationService.h

#ifndef ELEVATOR_SERVICES_STATE_NOTIFICATION_SERVICE_H
#define ELEVATOR_SERVICES_STATE_NOTIFICATION_SERVICE_H

#include "elevator/models/Elevator.h"
#include "core/event/StateChangeEvent.h"

namespace elevator::services {

    struct StateNotificationService {
        // Notify observers of a state change (door, heading, operation, elevator)
        template <typename StateVariant>
        static void NotifyStateChange(const Elevator& elevator, const StateVariant& stateVariant);
    };

}

#endif // ELEVATOR_SERVICES_STATE_NOTIFICATION_SERVICE_H