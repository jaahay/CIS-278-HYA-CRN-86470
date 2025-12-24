// elevator/Elevator.h
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <future>
#include <iostream>
#include <list>
#include <mutex>
#include <condition_variable>
#include "elevator/Passenger.h"
#include "elevator/Domain.h"
#include "core/Core.h"

namespace elevator {
    class Elevator {
    public:
        // Constructor for initial state
        explicit Elevator(int doorDelayMs = 1000, int moveDelayMs = 500, int currentFloor = 1);

        // Copy/move semantics
        Elevator(const Elevator&) = default;
        Elevator& operator=(const Elevator&) = default;
        Elevator(Elevator&&) noexcept = default;
        Elevator& operator=(Elevator&&) noexcept = default;

        // Comparison operator
        auto operator<=>(const Elevator&) const = default;

        // Accepts polymorphic domain-wide callback
        Elevator AddCallback(
            const core::StateChangeCallback<const core::detail::StateChangeEvent<DomainStateVariant>&>&) const;

        // Query functions
        constexpr int CurrentFloor() const;
        const bool IsIdle() const;

        /**
        * Calculate how inconvenient it would be to pick up a passenger. Cases:
        * 1. Same floor, doors opened and either stopped or same direction (0-distance)
        * 2. Stopped; no direction (distance between current floor and passenger's origin)
        * 3. Heading in same direction and away floor (twice distance between current and farthest + distance between current and passenger's origin)
        * 4. Heading in same direction on approach floor (distance between current and passenger's origin)
        * 5. Heading in opposite direction ( distance between farthest and current + distance between farthest and passenger's origin)
        */
        /*constexpr double Divergence(const Passenger&) const;
        std::future<std::list<const Passenger*>> ReceivePassenger(const Passenger&) const;
        std::future<bool> Wait() const;
        */
        constexpr double Divergence(const Passenger&) const;

        const std::future<Elevator> ReceivePassenger(const Passenger&) const;
        const std::future<bool> Wait() const;

        friend std::ostream& operator<<(std::ostream&, const Elevator&);
    private:

        const int doorDelayMs;
        const int moveDelayMs;
        const int current;

        const detail::OperationState* const operationState;
        const detail::DoorState* const doorState;
        const detail::Heading* const heading;

        mutable std::mutex activeMutex;
        mutable std::condition_variable activeCv;

        const std::list<const Passenger*> pendingPassengers;
        const std::list<const Passenger*> boardedPassengers;

        const core::StateChangeCallback<const core::detail::StateChangeEvent<DomainStateVariant>&> onStateChange;

        Elevator(
            int doorDelayMs,
            int moveDelayMs,
            int current,
            const detail::OperationState* operationState,
            const detail::DoorState* doorState,
            const detail::Heading* heading,
            std::list<const Passenger*> pendingPassengers,
            std::list<const Passenger*> boardedPassengers,
            core::StateChangeCallback<const core::detail::StateChangeEvent<DomainStateVariant>&> onStateChange
        );

        Elevator Transition(DomainStateVariant) const;

        const bool PassedOrigin(const Passenger&) const;
        const bool PassedDestination(const Passenger&) const;
        const bool FurtherToGo() const;
        /**
         * The farthest we must go at our current heading before we can change direction
         * Filter all pending passengers that we have not passed -> their Origin
         * Filter all boarded passengers ahead -> their Destination
         */
        const double FarthestToGo() const;

        // Asynchronous move returns a future with new Elevator state
        std::future<Elevator> MoveAsync() const;
        
        Elevator MoveStep() const;

        std::pair<std::list<const Passenger*>, bool> BoardPassengers() const;
        std::pair<std::list<const Passenger*>, bool> PassengersLeave() const;

        Elevator HandleBoardingDeparting() const;

        // Returns true if elevator should idle (no passengers)
        bool ShouldIdle() const;

        // Returns updated DoorState pointer after handling door closing
        Elevator HandleDoorClosing(const detail::DoorState*) const;

        // Returns updated Heading pointer after checking if direction should change
        Elevator UpdateHeadingIfNeeded(const detail::Heading*) const;

        // Returns new floor after moving one step in current heading
        int MoveOneFloor(int, const detail::Heading*) const;

    };
} // namespace elevator
#endif // ELEVATOR_H