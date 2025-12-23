// elevator/Elevator.cpp
#include "elevator/Elevator.h"

namespace elevator {
    Elevator::Elevator(int doorDelayMs, int moveDelayMs, int currentFloor)
        : doorDelayMs(doorDelayMs)
        , moveDelayMs(moveDelayMs)
        , current(currentFloor)
        , operationState(&DomainStates::Idle())
        , doorState(&DomainStates::DoorsOpened())
        , heading(&DomainStates::Stopped())
        , pendingPassengers()
        , boardedPassengers()
        , onStateChange()
    {
    }

    Elevator::Elevator(
        int doorDelayMs,
        int moveDelayMs,
        int current,
        const detail::OperationState* operationState,
        const detail::DoorState* doorState,
        const detail::Heading* heading,
        std::list<const Passenger*> pendingPassengers,
        std::list<const Passenger*> boardedPassengers,
        core::StateChangeCallback<const core::detail::StateChangeEvent<DomainStateVariant>&> onStateChange)
        : doorDelayMs(doorDelayMs)
        , moveDelayMs(moveDelayMs)
        , current(current)
        , operationState(operationState)
        , doorState(doorState)
        , heading(heading)
        , pendingPassengers(std::move(pendingPassengers))
        , boardedPassengers(std::move(boardedPassengers))
        , onStateChange(std::move(onStateChange))
    {
    }

    constexpr int Elevator::CurrentFloor() const {
        return current;
    }

    constexpr bool Elevator::IsIdle() const
    {
        return pendingPassengers.empty() && boardedPassengers.empty() && operationState == &DomainStates::Idle();
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

    const std::future<Elevator> Elevator::ReceivePassenger(const Passenger& passenger) const {
        return std::async(std::launch::async, [this, &passenger]() {
            auto newPending = pendingPassengers;
            if (std::find(newPending.begin(), newPending.end(), &passenger) == newPending.end()) {
                newPending.push_back(&passenger);
            }
            Elevator updatedElevator = Transition(&DomainStates::Active());
            // Immediately start moving after receiving passenger
            return updatedElevator.MoveStep();
            });
    }

    const std::future<bool> Elevator::Wait() const {
        return std::async(std::launch::async, [this]() {
            std::unique_lock<std::mutex> lock(activeMutex);
            activeCv.wait(lock, [this]() { return operationState->IsActive(); }); // wait until not active
            activeCv.notify_all();
            return true;
            });
    }

    // Compose a new Elevator with an additional domain state change observer callback
    Elevator Elevator::AddCallback(
        const core::StateChangeCallback<const core::detail::StateChangeEvent<DomainStateVariant>&>& cb) const
    {
        // Compose the existing callback with the new one, preserving immutability
        auto composedCallback = onStateChange.Compose(cb);

        // Return a new Elevator instance with the composed callback
        return Elevator(
            doorDelayMs,
            moveDelayMs,
            current,
            operationState,
            doorState,
            heading,
            pendingPassengers,
            boardedPassengers,
            std::move(composedCallback)
        );
    }

    Elevator Elevator::Transition(DomainStateVariant newState) const {
        auto newElevator = std::visit([this](auto&& statePtr) -> Elevator {
            if (statePtr == nullptr) {
                throw std::invalid_argument("Null pointer in DomainStateVariant");
            }
            using T = std::decay_t<decltype(*statePtr)>;

            if constexpr (std::is_base_of_v<detail::DoorState, T>) {
                return Elevator(doorDelayMs, moveDelayMs, current, operationState, statePtr, heading, pendingPassengers, boardedPassengers, onStateChange);
            }
            else if constexpr (std::is_base_of_v<detail::Heading, T>) {
                return Elevator(doorDelayMs, moveDelayMs, current, operationState, doorState, statePtr, pendingPassengers, boardedPassengers, onStateChange);
            }
            else if constexpr (std::is_base_of_v<detail::OperationState, T>) {
                return Elevator(doorDelayMs, moveDelayMs, current, statePtr, doorState, heading, pendingPassengers, boardedPassengers, onStateChange);
            }
            else {
                throw std::logic_error("Unhandled domain state type");
            }
            }, newState);

        if (newElevator.onStateChange) {
            core::detail::StateChangeEvent<DomainStateVariant> event(std::move(newState));
            newElevator.onStateChange(event);
        }

        return newElevator;
    }

    template<class>
    inline constexpr bool always_false = false;

    constexpr bool Elevator::PassedOrigin(const Passenger& passenger) const {
        if (*heading == DomainStates::GoingUp()) {
            return passenger.Origin() < current;
        }
        if (*heading == DomainStates::GoingDown()) {
            return passenger.Origin() > current;
        }
        return false;
    }

    constexpr bool Elevator::PassedDestination(const Passenger& passenger) const {
        if (*heading == DomainStates::GoingUp()) {
            return passenger.Destination() < current;
        }
        if (*heading == DomainStates::GoingDown()) {
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

    // Asynchronous Move method returning future Elevator state
    std::future<Elevator> Elevator::MoveAsync() const {
        return std::async(std::launch::async, [this]() {
            return this->MoveStep();
            });
    }

    Elevator Elevator::MoveStep() const {
        Elevator updated = *this;
         //Boarding/departing and door opening
        const DoorState* doorAfterBoardDepart = HandleBoardingDeparting();
        if (doorAfterBoardDepart != newDoorState) {
            newDoorState = doorAfterBoardDepart;
            if (onStateChange) onStateChange("DoorState", "DOORS_OPENING/OPENED");
        }

        // Idle check
        if (ShouldIdle()) {
            std::cout << "Elevator has come to a halt." << std::endl;
            newElevator = 
                Transition(DomainStateVariant{ &DomainStates::Idle() });
            newOperationState = newElevator.operationState;
            newHeading = newElevator.heading;
            if (onStateChange) {
                onStateChange("Heading", "STOPPED");
                onStateChange("OperationState", "IDLE");
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

    // Returns pair: (updated boardedPassengers, any passenger boarded)
    std::pair<std::list<const Passenger*>, bool> Elevator::BoardPassengers() const {
        bool boardedAny = false;
        std::list<const Passenger*> newBoarded(boardedPassengers);
        std::list<const Passenger*> newPending;

        for (const auto* passenger : pendingPassengers) {
            if (current == passenger->Origin() && (heading->IsStopped() || passenger->GoingMyWay(heading))) {
                std::cout << "Passenger " << *passenger << " is boarding.\n";
                newBoarded.push_back(passenger);
                boardedAny = true;
            }
            else {
                newPending.push_back(passenger);
            }
        }

        return { std::move(newBoarded), boardedAny };
    }

    // Returns pair: (updated boardedPassengers, any passenger left)
    std::pair<std::list<const Passenger*>, bool> Elevator::PassengersLeave() const {
        bool leftAny = false;
        std::list<const Passenger*> newBoarded;

        for (const auto* passenger : boardedPassengers) {
            if (current == passenger->Destination()) {
                std::cout << "Passenger " << *passenger << " is leaving.\n";
                leftAny = true;
            }
            else {
                newBoarded.push_back(passenger);
            }
        }

        return { std::move(newBoarded), leftAny };
    }
    
    Elevator Elevator::HandleBoardingDeparting() const {
        auto [newBoarded, boardedAny] = BoardPassengers();
        auto [newPending, leftAny] = PassengersLeave();

        if (boardedAny || leftAny) {
            std::cout << "Elevator servicing floor " << current << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(doorDelayMs));

            return Elevator(
                doorDelayMs,
                moveDelayMs,
                current,
                operationState,
                &DomainStates::DoorsOpened(),
                heading,
                std::move(newPending),
                std::move(newBoarded),
                onStateChange);
        }

        // No change, return *this
        return *this;
    }

    bool Elevator::ShouldIdle() const {
        return pendingPassengers.empty() && boardedPassengers.empty();
    }

    Elevator Elevator::HandleDoorClosing(const detail::DoorState* currentDoorState) const {
        if (*currentDoorState == DomainStates::DoorsOpened()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(doorDelayMs));
            std::cout << "Doors closed." << std::endl;

            return Transition(&DomainStates::DoorsClosed());
        }
        return *this;
    }

    Elevator Elevator::UpdateHeadingIfNeeded(const detail::Heading* currentHeading) const {
        if (!FurtherToGo()) {
            if (currentHeading->IsGoingUp()) {
                return Transition(&DomainStates::GoingDown());
            }
            else {
                return Transition(&DomainStates::GoingUp());
            }
        }
        return *this;
    }

    int Elevator::MoveOneFloor(int currentFloor, const detail::Heading* currentHeading) const {
        std::this_thread::sleep_for(std::chrono::milliseconds(moveDelayMs));
        if (currentHeading->IsGoingUp()) {
            return currentFloor + 1;
        }
        else if (currentHeading->IsGoingDown()) {
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