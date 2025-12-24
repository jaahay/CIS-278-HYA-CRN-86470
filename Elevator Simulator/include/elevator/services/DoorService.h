// elevator/services/DoorService.h
#ifndef ELEVATOR_SERVICES_DOOR_SERVICE_H
#define ELEVATOR_SERVICES_DOOR_SERVICE_H

#include "elevator/models/Elevator.h"

namespace elevator::services {

    struct DoorService {
        // Handle door closing logic, return updated Elevator with new door state
        static Elevator HandleDoorClosing(const Elevator& elevator);

        // Other door-related logic can go here
    };

} // namespace elevator::services

#endif // ELEVATOR_SERVICES_DOOR_SERVICE_H