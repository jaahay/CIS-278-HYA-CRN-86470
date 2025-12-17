#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <future>
#include <iostream>
#include <list>
#include "Passenger.h"
#include "ActiveState.h"
#include "DoorState.h"

class Elevator {
public:
    const bool IsIdle() const { return *state == IDLE; }
    /**
    * Calculate how inconvenient it would be to pick up a passenger. Cases:
    * 1. Same floor, doors opened and either stopped or same direction (0-distance)
    * 2. Stopped; no direction (distance between current floor and passenger's origin)
    * 3. Heading in same direction and away floor (twice distance between current and farthest + distance between current and passenger's origin)
    * 4. Heading in same direction on approach floor (distance between current and passenger's origin)
    * 5. Heading in opposite direction ( distance between farthest and current + distance between farthest and passenger's origin)
    */
    const double Divergence(const Passenger &) const;
    const std::future<std::list<const Passenger *>> ReceivePassenger(const Passenger &);
    const std::future<bool> Wait();
    friend std::ostream& operator<<(std::ostream& os, const Elevator& elevator) {
        os << "Currently at floor " << elevator.current << ". ";
        os << elevator.state << " " << elevator.doorState << " " << elevator.heading << ".";

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

    Elevator(int doorDelayMs = 5000, int moveDelayMs = 1000, int current = 1) :
        doorDelay(doorDelayMs), moveDelay(moveDelayMs), current(current),
        state(&IDLE), doorState(&DOORS_OPEN), heading(&STOPPED),
        pendingPassengers(), boardedPassengers() {
    }

    ~Elevator() = default;

    Elevator(const Elevator& other) :
        doorDelay(other.doorDelay), moveDelay(other.moveDelay), current(other.current),
        state(other.state), doorState(other.doorState), heading(other.heading),
        pendingPassengers(other.pendingPassengers), boardedPassengers(other.boardedPassengers) {
    }

    Elevator& operator=(const Elevator&) = delete;

    Elevator(Elevator&& other) noexcept :
        doorDelay(other.doorDelay), moveDelay(other.moveDelay), current(other.current),
        state(other.state), doorState(other.doorState), heading(other.heading),
        pendingPassengers(other.pendingPassengers), boardedPassengers(other.boardedPassengers) {
    }

    Elevator& operator=(Elevator&&) = delete;
    auto operator<=>(const Elevator &) const = default;

protected:

    int doorDelay;
    int moveDelay;
    int current;

    std::mutex active;

    const ActiveState* state;
    const DoorState* doorState;
    const Heading* heading;
    std::list<const Passenger*> pendingPassengers;
    std::list<const Passenger*> boardedPassengers;


    const bool PassedOrigin(const Elevator&, const Passenger&) const;
    const bool PassedDestination(const Elevator&, const Passenger&) const;

    /**
     * The farthest we must go at our current heading before we can change direction
     * Filter all pending passengers that we have not passed -> their Origin
     * Filter all boarded passengers ahead -> their Destination
     */
    const double FarthestToGo(const Elevator&) const;
    const bool FurtherToGo(const Elevator&) const;
    const bool Board(Elevator&);
    const bool Leave(Elevator&);
    const void MoveLoop(Elevator&);

    /**
      *  ... weight limit...
      *  ... elevator spread when no passengers no requests ...
     */
    const void Move(Elevator&);

private:
    bool DoorsOpen() const;
    void OpenDoors();
    void CloseDoors();
    bool Idle() const;

    bool GoingDown() const;
    bool GoingUp() const;
    bool Stopped() const;
    const Heading*& GoDown();
    const Heading*& GoUp();
    const Heading*& Stop();

    bool Active() const;
    const ActiveState*& Activate();
};

#endif // ELEVATOR_H
