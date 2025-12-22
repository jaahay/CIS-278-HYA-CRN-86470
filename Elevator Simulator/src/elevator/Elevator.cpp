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
        boardedPassengers() {
    }

    constexpr Elevator::Elevator(
        const int doorDelayMs,
        const int moveDelayMs,
        const int current,
        const OperationState* operationState,
        const DoorState* doorState,
        const Heading* heading,
        const std::list<const Passenger*>& pendingPassengers,
        const std::list<const Passenger*>& boardedPassengers
    )
        : doorDelayMs(doorDelayMs)
        , moveDelayMs(moveDelayMs)
        , current(current)
        , operationState(operationState)
        , doorState(doorState)
        , heading(heading)
        , pendingPassengers(std::move(pendingPassengers))
        , boardedPassengers(std::move(boardedPassengers))
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
            if (heading->PassedOrigin(*this, passenger)) {
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
            activeCv.wait(lock, [this]() { return *operationState != ACTIVE(); }); // wait until not active
            activeCv.notify_all();
            return true;
            });
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

    const Elevator Elevator::MoveStep() const {
        Elevator newElevator = Activate();

        int newFloor = newElevator.current;
        auto newOperationState = newElevator.operationState;
        auto newDoorState = newElevator.doorState;
        auto newHeading = newElevator.heading;

        bool board = newElevator.Board();
        bool depart = newElevator.Leave();

        /*if (elevator.pendingPassengers.empty() && elevator.boardedPassengers.empty()) {
            elevator.Stop();
        }*/

        if (board || depart) {
            std::cout << "An elevator is currently servicing floor " << current << std::endl;
            std::cout << this << std::endl;
            newDoorState = &DOORS_OPENING();
            std::cout << "Doors opening..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(doorDelayMs)); // Simulate door opening time
            newDoorState = &DOORS_OPENED();
        }

        if (pendingPassengers.empty() && boardedPassengers.empty()) {
            Deactivate();
        }
        else if (doorState->Opened()) {
            newDoorState = &DOORS_CLOSING();
            std::this_thread::sleep_for(std::chrono::milliseconds(doorDelayMs)); // Simulate door closing time
            newDoorState = &DOORS_CLOSED();
            std::cout << "Doors closed." << std::endl;
        }
        else if (!FurtherToGo()) {
            if (heading->IsGoingUp()) {
                newHeading = &GOING_DOWN();
            }
            else {
                newHeading = &GOING_UP();
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(moveDelayMs)); // Simulate time taken to move one floor
        if (heading->IsGoingUp()) {
            newFloor = current + 1;
        }
        if (heading->IsGoingDown()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(moveDelayMs)); // Simulate time taken to move one floor
            newFloor = current - 1;
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

    // Asynchronous Move method returning future Elevator state
    std::future<Elevator> Elevator::MoveAsync() const {
        return std::async(std::launch::async, [this]() {
            return this->MoveStep();
            });
    }

    constexpr bool Elevator::FurtherToGo() const {
        if (heading->IsStopped()) {
            return false;
        }

        if (boardedPassengers.empty()) {
            for (const auto& pendingPassenger : pendingPassengers) {
                if (!heading->GoingMyWay(*pendingPassenger)) {
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
            if (!heading->PassedOrigin(*this, *pendingPassenger)) {
                forwardStops.push_back(pendingPassenger->Origin());
            }
        }

        for (const auto& boardedPassenger : boardedPassengers) {
            if (!heading->PassedDestination(*this, *boardedPassenger)) {
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