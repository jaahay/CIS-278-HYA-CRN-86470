// elevator/Elevator.h
#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <future>
#include <iostream>
#include <list>
#include "States.h"
#include "Passenger.h"

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
        constexpr double Divergence(const Passenger&) const;

        std::future<Elevator> ReceivePassenger(const Passenger&) const;
        std::future<bool> Wait() const;

        friend std::ostream& operator<<(std::ostream&, const Elevator&);
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
        friend std::ostream& operator<<(std::ostream&, const Elevator&);
    private:

        const int doorDelayMs;
        const int moveDelayMs;
        const int current;

        constexpr explicit Elevator(
            const int,
            const int,
            const int,
            const OperationState*,
            const DoorState*,
            const Heading*,
            const std::list<const Passenger*>&,
            const std::list<const Passenger*>&);

        // Asynchronous move returns a future with new Elevator state
        std::future<Elevator> MoveAsync() const;

        const OperationState* operationState;
        const DoorState* doorState;
        const Heading* heading;

        mutable std::mutex activeMutex;
        mutable std::condition_variable activeCv;

        const std::list<const Passenger*> pendingPassengers;
        const std::list<const Passenger*> boardedPassengers;

        constexpr bool DoorsOpened() const;
        constexpr bool DoorsClosed() const;


        constexpr bool FurtherToGo() const;
        /**
         * The farthest we must go at our current heading before we can change direction
         * Filter all pending passengers that we have not passed -> their Origin
         * Filter all boarded passengers ahead -> their Destination
         */
        constexpr double FarthestToGo() const;
        constexpr bool Board() const;
        constexpr bool Leave() const;

        const Elevator Activate() const;
        const Elevator Deactivate() const;
        const Elevator MoveStep() const;
    };
} // namespace elevator
#endif // ELEVATOR_H