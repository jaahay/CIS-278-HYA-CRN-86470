#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <future>
#include <iostream>
#include <list>
#include "ActiveState.h"
#include "DoorState.h"
#include "ElevatorConcepts.h"
#include "Passenger.h"

//template<class E, class P> class Elevator;

template<class E, class Passenger>
requires ElevatorConcept<E, Passenger>
class Elevator {
public:
    constexpr bool IsIdle() const;
    /**
    * Calculate how inconvenient it would be to pick up a passenger. Cases:
    * 1. Same floor, doors opened and either stopped or same direction (0-distance)
    * 2. Stopped; no direction (distance between current floor and passenger's origin)
    * 3. Heading in same direction and away floor (twice distance between current and farthest + distance between current and passenger's origin)
    * 4. Heading in same direction on approach floor (distance between current and passenger's origin)
    * 5. Heading in opposite direction ( distance between farthest and current + distance between farthest and passenger's origin)
    */
    constexpr double Divergence(const Passenger &) const;
    constexpr std::future<std::list<const Passenger *>> ReceivePassenger(const Passenger &) const;
    constexpr std::future<bool> Wait() const;
    friend std::ostream& operator<<(std::ostream&, const E&);

    explicit Elevator(int doorDelay = 5000, int moveDelayMs = 1000, int current = 1);
    ~Elevator() = default;

    Elevator(const Elevator&) = delete;
    Elevator& operator=(const Elevator&) = delete;
    Elevator(Elevator&&) noexcept = default;
    Elevator& operator=(Elevator&&) noexcept = default;
    auto operator<=>(const Elevator &) const = default;

protected:

    const int doorDelayMs;
    const int moveDelayMs;
    const int current;

    std::mutex active;

    const std::unique_ptr<ActiveState<ActiveState>> state;
    const std::unique_ptr<DoorState> doorState;
    const std::unique_ptr<Heading> heading;
    const std::list<const P*> pendingPassengers;
    const std::list<const P*> boardedPassengers;

    constexpr bool PassedOrigin(const P&) const;
    constexpr bool PassedDestination(const P&) const;

    /**
     * The farthest we must go at our current heading before we can change direction
     * Filter all pending passengers that we have not passed -> their Origin
     * Filter all boarded passengers ahead -> their Destination
     */
    constexpr double FarthestToGo() const;
    constexpr bool FurtherToGo() const;
    constexpr bool Board() const;
    constexpr bool Leave() const;
    constexpr void MoveLoop() const;

    /**
      *  ... weight limit...
      *  ... elevator spread when no passengers no requests ...
     */
    constexpr void Move() const;

private:
    constexpr explicit Elevator(
        const int doorDelayMs,
        const int moveDelayMs,
        const int current,
        const std::unique_ptr<ActiveState>,
        const std::unique_ptr<DoorState>,
        const std::unique_ptr<Heading>,
        const std::list<const P*> pendingPassengers,
        const std::list<const P*> boardedPassengers);

    constexpr bool DoorsOpen() const;
    constexpr E& OpenDoors() const;
    constexpr E& CloseDoors() const;
    constexpr E& Idle() const;

    constexpr bool GoingDown() const;
    constexpr bool GoingUp() const;
    constexpr bool Stopped() const;
    constexpr E& GoDown() const;
    constexpr E& GoUp() const;
    constexpr E& Stop() const;

    constexpr bool Active() const;
    constexpr E& Activate() const;
};

#endif // ELEVATOR_H