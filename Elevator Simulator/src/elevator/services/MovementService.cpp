// elevator/services/MovementService.cpp
#include "elevator/services/MovementService.h"
#include "elevator/states/ElevatorStateVariants.h"

namespace elevator::services {

    int MovementService::MoveOneFloor(const Elevator& elevator) {
        int currentFloor = elevator.CurrentFloor();
        const auto* heading = elevator.GetHeading();

        if (heading == &ElevatorStates::GoingUp()) {
            return currentFloor + 1;
        }
        else if (heading == &ElevatorStates::GoingDown()) {
            return currentFloor - 1;
        }
        else {
            return currentFloor; // Stopped or unknown heading
        }
    }

    Elevator MovementService::UpdateHeadingIfNeeded(const Elevator& elevator) {
        if (!PassengerService::FurtherToGo(elevator)) {
            const auto* currentHeading = elevator.GetHeading();
            if (currentHeading->IsGoingUp()) {
                return elevator.Transition(&ElevatorStates::GoingDown());
            }
            else {
                return elevator.Transition(&ElevatorStates::GoingUp());
            }
        }
        return elevator;
    }

    bool MovementService::ShouldIdle(const Elevator& elevator) {
        return elevator.GetPendingPassengers().empty() && elevator.GetBoardedPassengers().empty();
    }

} // namespace elevator::services
