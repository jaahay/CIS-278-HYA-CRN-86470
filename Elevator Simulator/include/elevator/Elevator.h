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
        constexpr Elevator(int doorDelayMs, int moveDelayMs, int currentFloor);

        // Copy/move semantics
        Elevator(const Elevator&) = default;
        Elevator& operator=(const Elevator&) = default;
        Elevator(Elevator&&) noexcept = default;
        Elevator& operator=(Elevator&&) noexcept = default;

        // Comparison operator
        auto operator<=>(const Elevator&) const = default;

        // Query functions
        constexpr int CurrentFloor() const;
        constexpr bool IsIdle() const;

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

        std::future<Elevator> ReceivePassenger(const Passenger&) const;
        std::future<bool> Wait() const;
        Elevator AddCallback(core::StateChangeCallback<const core::detail::StateChangeEvent<detail::DoorState>&>) const;

        friend std::ostream& operator<<(std::ostream&, const Elevator&);
        friend std::ostream& operator<<(std::ostream&, const Elevator&);
    private:

        const int doorDelayMs;
        const int moveDelayMs;
        const int current;

        const detail::OperationState* operationState;
        const detail::DoorState* doorState;
        const detail::Heading* heading;

        mutable std::mutex activeMutex;
        mutable std::condition_variable activeCv;

        const std::list<const Passenger*> pendingPassengers;
        const std::list<const Passenger*> boardedPassengers;

        core::StateChangeCallback<const core::detail::StateChangeEvent<detail::DoorState>&> onStateChange;

        Elevator(
            int doorDelayMs,
            int moveDelayMs,
            int current,
            const detail::OperationState*,
            const detail::DoorState*,
            const detail::Heading*,
            std::list<const Passenger*>,
            std::list<const Passenger*>,
            core::StateChangeCallback<const core::detail::StateChangeEvent<detail::DoorState>&>
        );

        constexpr bool PassedOrigin(const Passenger&) const;
        constexpr bool PassedDestination(const Passenger&) const;
        constexpr bool FurtherToGo() const;
        /**
         * The farthest we must go at our current heading before we can change direction
         * Filter all pending passengers that we have not passed -> their Origin
         * Filter all boarded passengers ahead -> their Destination
         */
        constexpr double FarthestToGo() const;

        const Elevator Activate() const;
        const Elevator Deactivate() const;

        // Asynchronous move returns a future with new Elevator state
        std::future<Elevator> MoveAsync() const;
        
        const Elevator MoveStep() const;// Returns updated DoorState pointer after handling boarding/departing

        constexpr bool Board() const;
        constexpr bool Leave() const;

        const detail::DoorState* HandleBoardingDeparting() const;

        // Returns true if elevator should idle (no passengers)
        bool ShouldIdle() const;

        // Returns updated DoorState pointer after handling door closing
        const detail::DoorState* HandleDoorClosing(const detail::DoorState* currentDoorState) const;

        // Returns updated Heading pointer after checking if direction should change
        const detail::Heading* UpdateHeadingIfNeeded(const detail::Heading* currentHeading) const;

        // Returns new floor after moving one step in current heading
        int MoveOneFloor(int currentFloor, const detail::Heading* currentHeading) const;

    };
} // namespace elevator
#endif // ELEVATOR_H