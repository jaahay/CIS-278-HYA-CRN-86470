#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <future>
#include <iostream>
#include <list>
#include "Passenger.h"
#include "ElevatorConcepts.h"

template <
    typename PassengerType,
    typename ActiveStateType,
    typename DoorStateType,
    typename HeadingType
>
    requires ElevatorConcept<
        Elevator<PassengerType, ActiveStateType, DoorStateType, HeadingType>,
            PassengerType
    >
class Elevator {

public:
    using _ActiveStateType = ActiveStateType;
    using _DoorStateType = DoorStateType;
    using _HeadingType = HeadingType;
    constexpr Elevator<PassengerType, ActiveStateType, DoorStateType, HeadingType>(
        int doorDelayMs,
        int moveDelayMs,
        int current
    );

    ~Elevator() = default;

    Elevator(const Elevator&) = delete;
    Elevator& operator=(const Elevator&) = delete;
    Elevator(Elevator&&) noexcept = default;
    Elevator& operator=(Elevator&&) noexcept = default;
    auto operator<=>(const Elevator&) const = default;
    constexpr bool IsIdle() const;
    /**
    * Calculate how inconvenient it would be to pick up a passenger. Cases:
    * 1. Same floor, doors opened and either stopped or same direction (0-distance)
    * 2. Stopped; no direction (distance between current floor and passenger's origin)
    * 3. Heading in same direction and away floor (twice distance between current and farthest + distance between current and passenger's origin)
    * 4. Heading in same direction on approach floor (distance between current and passenger's origin)
    * 5. Heading in opposite direction ( distance between farthest and current + distance between farthest and passenger's origin)
    */
    constexpr double Divergence(const PassengerType &) const;
    constexpr std::future<std::list<const PassengerType *>> ReceivePassenger(const PassengerType &) const;
    constexpr std::future<bool> Wait() const;
    friend std::ostream& operator<<(std::ostream&, const Elevator&);
protected:

    const int doorDelayMs;
    const int moveDelayMs;
    const int current;

    std::mutex active;

    const std::unique_ptr<const ActiveStateType> state;
    const std::unique_ptr<const DoorStateType> doorState;
    const std::unique_ptr<const HeadingType> heading;
    const std::list<const Passenger*> pendingPassengers;
    const std::list<const Passenger*> boardedPassengers;

    constexpr bool PassedOrigin(const PassengerType&) const;
    constexpr bool PassedDestination(const PassengerType&) const;

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
        const std::unique_ptr<ActiveStateType>,
        const std::unique_ptr<DoorStateType>,
        const std::unique_ptr<HeadingType>,
        const std::list<const PassengerType*> pendingPassengers,
        const std::list<const PassengerType*> boardedPassengers);

    constexpr bool DoorsOpen() const;
    constexpr Elevator& OpenDoors() const;
    constexpr Elevator& CloseDoors() const;
    constexpr Elevator& Idle() const;

    constexpr bool GoingDown() const;
    constexpr bool GoingUp() const;
    constexpr bool Stopped() const;
    constexpr Elevator& GoDown() const;
    constexpr Elevator& GoUp() const;
    constexpr Elevator& Stop() const;

    constexpr bool Active() const;
    constexpr Elevator& Activate() const;
};
#endif // ELEVATOR_H