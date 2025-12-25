// elevator/services/ElevatorPassengerService.cpp
#include "elevator/services/ElevatorPassengerService.h"

#include "elevator/models/Elevator.h"
#include "elevator/models/Passenger.h"

#include <algorithm>
#include <iostream>

namespace elevator::services {

    Elevator ElevatorPassengerService::AddPendingPassenger(const Elevator& elevator, std::shared_ptr<const Passenger> passenger) {
        auto newPending = elevator.GetPendingPassengers();

        // Prevent duplicates by comparing shared_ptr addresses or Passenger content
        auto it = std::find_if(newPending.begin(), newPending.end(),
            [&passenger](const std::shared_ptr<const Passenger>& p) { return p == passenger; });

        if (it == newPending.end()) {
            newPending.push_back(passenger);
        }

        return Elevator(
            elevator.doorDelayMs_,
            elevator.moveDelayMs_,
            elevator.CurrentFloor(),
            elevator.GetOperationState(),
            elevator.GetDoorState(),
            elevator.GetHeading(),
            std::move(newPending),
            elevator.GetBoardedPassengers(),
            elevator.onStateChange_
        );
    }

    constexpr double ElevatorPassengerService::Divergence(const Elevator& elevator, const Passenger& passenger) const {
        // std::cout << "Check ";
        // passenger.print(std::cout);

        if (Stopped()) {
            if (current == passenger.Origin() && DoorsOpen() &&
                (Idle() || passenger.GoingMyWay(*heading))
                ) {
                return 0;
            }

            if (Idle()) {
                return std::abs(current - passenger.Origin());
            }
        }

        if (passenger.GoingMyWay(*heading)) {
            if (PassedOrigin(passenger)) {
                return 2 * std::abs(current - FarthestToGo()) + std::abs(current - passenger.Origin());
            }
            else {
                return std::abs(current - passenger.Origin());
            }
        }

        if (!passenger.GoingMyWay(*heading)) {
            double f = FarthestToGo();
            return std::abs(f - current) + std::abs(f - passenger.Origin());
        }

        throw std::invalid_argument("Invalid heading for elevator.");
    }

    constexpr bool ElevatorPassengerService::PassedOrigin(const Elevator& elevator, const Passenger& passenger) const {
        if (Stopped()) { return false; }
        return GoingDown() && passenger.Origin() > current || GoingUp() && passenger.Origin() < current;
    }

    constexpr bool ElevatorPassengerService::PassedDestination(const Elevator& elevator, const Passenger& passenger) const {
        if (Stopped()) { return false; }
        return GoingDown() && passenger.Destination() > current || GoingUp() && passenger.Destination() < current;
    }
    bool ElevatorPassengerService::FurtherToGo(const Elevator& elevator) {
        const auto* heading = elevator.GetHeading();
        int current = elevator.CurrentFloor();

        if (heading->IsStopped()) {
            return false;
        }

        if (elevator.GetBoardedPassengers().empty()) {
            for (const auto& pendingPassenger : elevator.GetPendingPassengers()) {
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

        for (const auto& boardedPassenger : elevator.GetBoardedPassengers()) {
            if (heading->IsGoingUp() && boardedPassenger->Destination() > current) {
                return true;
            }
            if (heading->IsGoingDown() && boardedPassenger->Destination() < current) {
                return true;
            }
        }

        return false;
    }

    double ElevatorPassengerService::FarthestToGo(const Elevator& elevator) {
        std::vector<int> forwardStops;

        for (const auto& pendingPassenger : elevator.GetPendingPassengers()) {
            if (!PassedOrigin(elevator, *pendingPassenger)) {
                forwardStops.push_back(pendingPassenger->Origin());
            }
        }

        for (const auto& boardedPassenger : elevator.GetBoardedPassengers()) {
            if (!PassedDestination(elevator, *boardedPassenger)) {
                forwardStops.push_back(boardedPassenger->Destination());
            }
        }

        if (forwardStops.empty()) {
            return static_cast<double>(elevator.CurrentFloor());
        }

        if (elevator.GetHeading()->IsGoingUp()) {
            return static_cast<double>(*std::max_element(forwardStops.begin(), forwardStops.end()));
        }
        else if (elevator.GetHeading()->IsGoingDown()) {
            return static_cast<double>(*std::min_element(forwardStops.begin(), forwardStops.end()));
        }
        else {
            return static_cast<double>(elevator.CurrentFloor());
        }
    }

    std::pair<std::list<std::shared_ptr<const Passenger>>, bool> ElevatorPassengerService::PassengersLeave(
        const Elevator& elevator) {

        bool leftAny = false;
        std::list<std::shared_ptr<const Passenger>> newBoarded;
        int current = elevator.CurrentFloor();

        for (const auto& passenger : elevator.GetBoardedPassengers()) {
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

    std::pair<std::list<std::shared_ptr<const Passenger>>, bool> ElevatorPassengerService::BoardPassengers(
        const Elevator& elevator) {

        bool boardedAny = false;
        std::list<std::shared_ptr<const Passenger>> newBoarded = elevator.GetBoardedPassengers();
        std::list<std::shared_ptr<const Passenger>> newPending;

        int current = elevator.CurrentFloor();
        const auto* heading = elevator.GetHeading();

        for (const auto& pendingPassenger : elevator.GetPendingPassengers()) {
            if (pendingPassenger->Origin() == current && pendingPassenger->GoingMyWay(heading)) {
                newBoarded.push_back(pendingPassenger);
                boardedAny = true;
                std::cout << "Passenger " << *pendingPassenger << " is boarding.\n";
            }
            else {
                newPending.push_back(pendingPassenger);
            }
        }

        return { std::move(newBoarded), boardedAny };
    }

    Elevator ElevatorPassengerService::HandleBoardingDeparting(const Elevator& elevator) {
        auto [newBoarded, boardedAny] = BoardPassengers(elevator);
        auto [newBoardedAfterLeave, leftAny] = PassengersLeave(
            Elevator(
                elevator.doorDelayMs_,
                elevator.moveDelayMs_,
                elevator.CurrentFloor(),
                elevator.GetOperationState(),
                elevator.GetDoorState(),
                elevator.GetHeading(),
                elevator.GetPendingPassengers(),
                std::move(newBoarded),
                elevator.onStateChange_));

        if (boardedAny || leftAny) {
            std::cout << "Elevator servicing floor " << elevator.CurrentFloor() << std::endl;

            // Door delay should be handled externally to avoid blocking here
            // std::this_thread::sleep_for(std::chrono::milliseconds(elevator.doorDelayMs_));

            return Elevator(
                elevator.doorDelayMs_,
                elevator.moveDelayMs_,
                elevator.CurrentFloor(),
                elevator.GetOperationState(),
                &DomainStates::DoorsOpened(),
                elevator.GetHeading(),
                elevator.GetPendingPassengers(),
                std::move(newBoardedAfterLeave),
                elevator.onStateChange_);
        }

        return elevator;
    }
} // namespace elevator::services
