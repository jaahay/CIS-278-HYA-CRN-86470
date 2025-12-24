// elevator/services/DoorService.cpp
#include "elevator/services/DoorService.h"

namespace elevator::services {

    Elevator DoorService::HandleDoorClosing(const Elevator& elevator) {
        if (*elevator.GetDoorState() == ElevatorStates::DoorsOpened()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(elevator.doorDelayMs_)); // friend access or getter

            std::cout << "Doors closed." << std::endl;

            return elevator.Transition(&ElevatorStates::DoorsClosed());
        }
        return elevator;
    }

} // namespace elevator::services
