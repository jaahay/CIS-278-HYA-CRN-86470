// elevator/Elevator.cpp
#include "elevator/Elevator.h"

namespace elevator {
    constexpr Elevator::Elevator(
        int doorDelayMs,
        int moveDelayMs,
        int current
    ) :
        doorDelayMs(doorDelayMs),
        moveDelayMs(moveDelayMs),
        current(current),
        operationState(&IDLE()),
        doorState(&DOORS_OPENED()),
        heading(&STOPPED()),
        pendingPassengers(),
        boardedPassengers(),
        onStateChange({}) {
    }

    constexpr Elevator::Elevator(
        const int doorDelayMs,
        const int moveDelayMs,
        const int current,
        const OperationState* operationState,
        const DoorState* doorState,
        const Heading* heading,
        const std::list<const Passenger*>& pendingPassengers,
        const std::list<const Passenger*>& boardedPassengers,
        const StateChangeCallback onStateChange
    )
        : doorDelayMs(doorDelayMs)
        , moveDelayMs(moveDelayMs)
        , current(current)
        , operationState(operationState)
        , doorState(doorState)
        , heading(heading)
        , pendingPassengers(std::move(pendingPassengers))
        , boardedPassengers(std::move(boardedPassengers))
        , onStateChange(onStateChange)
    { };

    constexpr int Elevator::CurrentFloor() const {
        return current;
    }

    constexpr bool Elevator::IsIdle() const
    {
        return *operationState == IDLE();
    }

    constexpr double Elevator::Divergence(const Passenger& passenger) const {
        // std::cout << "Check ";
        // passenger.print(std::cout);

        if (heading->IsStopped()) {
            if (current == passenger.Origin() && doorState->Opened() &&
                (IsIdle() || passenger.GoingMyWay(heading))
                ) {
                return 0;
            }

            if (IsIdle()) {
                return std::abs(current - passenger.Origin());
            }
        }

        if (passenger.GoingMyWay(heading)) {
            if (PassedOrigin(passenger)) {
                return 2 * std::abs(current - FarthestToGo()) + std::abs(current - passenger.Origin());
            }
            else {
                return std::abs(current - passenger.Origin());
            }
        }

        if (!passenger.GoingMyWay(heading)) {
            double f = FarthestToGo();
            return std::abs(f - current) + std::abs(f - passenger.Origin());
        }

        throw std::invalid_argument("Invalid heading for elevator.");
    }

    std::future<Elevator> Elevator::ReceivePassenger(const Passenger& passenger) const {
        return std::async(std::launch::async, [this, &passenger]() {
            auto newPending = pendingPassengers;
            if (std::find(newPending.begin(), newPending.end(), &passenger) == newPending.end()) {
                newPending.push_back(&passenger);
            }
            Elevator updatedElevator(
                doorDelayMs,
                moveDelayMs,
                current,
                operationState,
                doorState,
                heading,
                std::move(newPending),
                boardedPassengers
            );
            // Immediately start moving after receiving passenger
            return updatedElevator.MoveStep();
            });
    }

    std::future<bool> Elevator::Wait() const {
        return std::async(std::launch::async, [this]() {
            std::unique_lock<std::mutex> lock(activeMutex);
            activeCv.wait(lock, [this]() { return operationState->IsActive(); }); // wait until not active
            activeCv.notify_all();
            return true;
            });
    }

    // Compose a new Elevator with an additional observer callback
    Elevator Elevator::AddCallback(const StateChangeCallback& cb) const {
        return Elevator(
            doorDelayMs,
            moveDelayMs,
            current,
            operationState,
            doorState,
            heading,
            pendingPassengers,
            boardedPassengers,
            onStateChange.Compose(cb)
        );
    }

    constexpr bool Elevator::PassedOrigin(const Passenger& passenger) const {
        if (heading == &GOING_UP()) {
            return passenger.Origin() < current;
        }
        if (heading == &GOING_DOWN()) {
            return passenger.Origin() > current;
        }
        return false;
    }

    constexpr bool Elevator::PassedDestination(const Passenger& passenger) const {
        if (heading == &GOING_UP()) {
            return passenger.Destination() < current;
        }
        if (heading == &GOING_DOWN()) {
            return passenger.Destination() > current;
        }
    }

    constexpr bool Elevator::FurtherToGo() const {
        if (heading->IsStopped()) {
            return false;
        }

        if (boardedPassengers.empty()) {
            for (const auto& pendingPassenger : pendingPassengers) {
                if (!pendingPassenger->GoingMyWay(heading)) {
                    continue;
                }
                if (heading->IsGoingUp() && pendingPassenger->Origin() > current) {
                    return true;
                }
                if (heading->IsGoingDown() && pendingPassenger->Origin() < current) {
                    return true;
                }
            }
        }

        for (const auto& boardedPassenger : boardedPassengers) {
            if (heading->IsGoingUp() && boardedPassenger->Destination() > current) {
                return true;
            }
            if (heading->IsGoingDown() && boardedPassenger->Destination() < current) {
                return true;
            }
        }

        return false;
    }

    constexpr double Elevator::FarthestToGo() const {
        std::list<double> forwardStops;

        for (const auto& pendingPassenger : pendingPassengers) {
            if (!PassedOrigin(*pendingPassenger)) {
                forwardStops.push_back(pendingPassenger->Origin());
            }
        }

        for (const auto& boardedPassenger : boardedPassengers) {
            if (!PassedDestination(*boardedPassenger)) {
                forwardStops.push_back(boardedPassenger->Destination());
            }
        }

        if (forwardStops.empty()) {
            // No stops ahead; return current floor as fallback
            return static_cast<double>(current);
        }

        if (heading->IsGoingUp()) {
            return *std::max_element(forwardStops.begin(), forwardStops.end());
        }
        else if (heading->IsGoingDown()) {
            return *std::min_element(forwardStops.begin(), forwardStops.end());
        }
        else {
            // If stopped or unknown heading, return current floor
            return static_cast<double>(current);
        }
    }

    const Elevator Elevator::Activate() const {
        return Elevator(
            doorDelayMs,
            moveDelayMs,
            current,
            &ACTIVE(),
            doorState,
            heading,
            pendingPassengers,
            boardedPassengers
        );
    }

    const Elevator Elevator::Deactivate() const {
        std::cout << "Elevator has come to a halt." << std::endl;
        return Elevator(
            doorDelayMs,
            moveDelayMs,
            current,
            &IDLE(),
            doorState,
            &STOPPED(),
            pendingPassengers,
            boardedPassengers
        );
    }

    // Asynchronous Move method returning future Elevator state
    std::future<Elevator> Elevator::MoveAsync() const {
        return std::async(std::launch::async, [this]() {
            return this->MoveStep();
            });
    }

    const Elevator Elevator::MoveStep() const {
        Elevator newElevator = Activate();

        int newFloor = newElevator.current;
        auto newOperationState = newElevator.operationState;
        auto newDoorState = newElevator.doorState;
        auto newHeading = newElevator.heading;

        // Boarding/departing and door opening
        const DoorState* doorAfterBoardDepart = HandleBoardingDeparting();
        if (doorAfterBoardDepart != newDoorState) {
            newDoorState = doorAfterBoardDepart;
            if (onStateChange) onStateChange("DoorState", "DOORS_OPENING/OPENED");
        }

        // Idle check
        if (ShouldIdle()) {
            newElevator = Deactivate();
            newOperationState = newElevator.operationState;
            newHeading = newElevator.heading;
            if (onStateChange) {
                onStateChange("OperationState", "IDLE");
                onStateChange("Heading", "STOPPED");
            }
        }
        else {
            // Door closing if doors are open
            const DoorState* doorAfterClosing = HandleDoorClosing(newDoorState);
            if (doorAfterClosing != newDoorState) {
                newDoorState = doorAfterClosing;
                if (onStateChange) onStateChange("DoorState", "DOORS_CLOSING/CLOSED");
            }

            // Update heading if needed
            const Heading* updatedHeading = UpdateHeadingIfNeeded(newHeading);
            if (updatedHeading != newHeading) {
                newHeading = updatedHeading;
                if (onStateChange) {
                    std::string headingStr = (newHeading->IsGoingUp()) ? "GOING_UP" : "GOING_DOWN";
                    onStateChange("Heading", headingStr);
                }
            }
        }

        // Move elevator one floor
        int movedFloor = MoveOneFloor(newFloor, newHeading);
        if (movedFloor != newFloor) {
            newFloor = movedFloor;
            if (onStateChange) onStateChange("Floor", std::to_string(newFloor));
        }

        return Elevator(
            doorDelayMs,
            moveDelayMs,
            newFloor,
            newOperationState,
            newDoorState,
            newHeading,
            pendingPassengers,
            boardedPassengers
        );
    };


    constexpr bool Elevator::Board() const {
        bool board = false;
        if (!pendingPassengers.empty()) {
            for (auto passenger& = pendingPassengers.begin(); passenger != pendingPassengers.end();) {
                if (current == passenger->Origin() && (heading->IsStopped() || passenger->GoingMyWay(heading))) {
                    std::cout << "Passenger " << *passenger << " is boarding. " << std::endl;
                    boardedPassengers.push_back(*passenger);
                    passenger = pendingPassengers.erase(passenger);
                    board = true;
                }
                else {
                    ++passenger;
                }
            }
        }
        return board;
    };

    constexpr bool Elevator::Leave() const {
        bool leave = false;
        if (!boardedPassengers.empty()) {
            for (auto boardedPassenger = boardedPassengers.begin(); boardedPassenger != boardedPassengers.end();) {
                if (current == (*boardedPassenger)->Destination()) {
                    std::cout << std::endl << "Passenger " << *boardedPassenger << " is leaving." << std::endl;
                    boardedPassenger = boardedPassengers.erase(boardedPassenger);
                    leave = true;
                }
                else {
                    ++boardedPassenger;
                }
            }
        }
        return leave;
    };  
    
    const DoorState* Elevator::HandleBoardingDeparting() const {
        bool board = Board();
        bool depart = Leave();

        if (board || depart) {
            std::cout << "An elevator is currently servicing floor " << current << std::endl;
            std::cout << this << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(doorDelayMs));
            return &DOORS_OPENED();
        }
        return doorState;
    }

    bool Elevator::ShouldIdle() const {
        return pendingPassengers.empty() && boardedPassengers.empty();
    }

    const DoorState* Elevator::HandleDoorClosing(const DoorState* currentDoorState) const {
        if (*currentDoorState == DOORS_OPENED()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(doorDelayMs));
            std::cout << "Doors closed." << std::endl;
            return &DOORS_CLOSED();
        }
        return currentDoorState;
    }

    const Heading* Elevator::UpdateHeadingIfNeeded(const Heading* currentHeading) const {
        if (!FurtherToGo()) {
            if (currentHeading->IsGoingUp()) {
                return &GOING_DOWN();
            }
            else {
                return &GOING_UP();
            }
        }
        return currentHeading;
    }

    int Elevator::MoveOneFloor(int currentFloor, const Heading* currentHeading) const {
        std::this_thread::sleep_for(std::chrono::milliseconds(moveDelayMs));
        if (currentHeading->IsGoingUp()) {
            return currentFloor + 1;
        }
        else if (currentHeading->IsGoingDown()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(moveDelayMs));
            return currentFloor - 1;
        }
        return currentFloor;
    }

    std::ostream& operator<<(std::ostream& os, const Elevator& elevator) {
        os << "Currently at floor " << elevator.current << ". ";
        os << elevator.operationState << " " << elevator.doorState << " " << elevator.heading << ".";

        if (!elevator.boardedPassengers.empty()) {
            os << std::endl << "\t" << elevator.boardedPassengers.size() << " boarded passenger(s): ";
            for (auto boardedPassenger = elevator.boardedPassengers.begin(); boardedPassenger != std::prev(elevator.boardedPassengers.end());) {
                os << *boardedPassenger << ", ";
                ++boardedPassenger;
            }
            os << elevator.boardedPassengers.back();
        }

        if (!elevator.pendingPassengers.empty()) {
            os << std::endl << "\t" << elevator.pendingPassengers.size() << " awaiting passenger(s): ";
            for (auto pendingPassenger = elevator.pendingPassengers.begin(); pendingPassenger != std::prev(elevator.pendingPassengers.end());) {
                os << *pendingPassenger << ", ";
                ++pendingPassenger;
            }
            os << elevator.pendingPassengers.back();
        }
        return os;
    };
}