#ifndef ELEVATOR_CONCEPTS_H
#define ELEVATOR_CONCEPTS_H
#include <concepts>
#include <future>
#include <ActiveState.h>
#include <DoorState.h>
#include <Heading.h>

template <typename E, typename P>
concept ElevatorConceptConstPublic = requires(const E elevator, const P passenger) {
	{ elevator.IsIdle() } -> std::convertible_to<bool>;
	{ elevator.Divergive(passenger) } -> std::convertible_to<const double>;
};

template <typename E, typename P>
concept ElevatorConceptPublic = requires(E elevator, const P passenger) {
	{ elevator.ReceivePassenger(passenger) } -> std::convertible_to < std::future<std::list<const P*>>>;
	{ elevator.Wait() } -> std::convertible_to<std::future<bool>>;
};

template <
    typename E, typename P,
    typename ActiveStateType, typename DoorStateType, typename HeadingType
>
concept ElevatorConceptConstProtected = requires(const E elevator, const P passenger) {
    { elevator.state } -> std::convertible_to<ActiveStateType>;
    { elevator.doorState } -> std::convertible_to<DoorStateType>;
    { elevator.heading } -> std::convertible_to<HeadingType>;
    { elevator.pendingPassenger } -> std::convertible_to<std::list<P>>;
    { elevator.boardedPassengers } -> std::convertible_to<std::list<P>>;
    { elevator.PassedOrigin(passenger) } -> std::convertible_to<bool>;
    { elevator.PassedDestination(passenger) } -> std::convertible_to<bool>;
    { elevator.FarthestToGo() } -> std::convertible_to<double>;
    { elevator.FurtherToGo() } -> std::convertible_to<bool>;
};

template <typename E>
concept ElevatorConceptProtected = requires(E elevator) {
	{ elevator.Board() } -> std::convertible_to<bool>;
	{ elevator.Leave() } -> std::convertible_to<bool>;
	{ elevator.MoveLoop() };
	{ elevator.Move() };
};

template<typename E, typename P>
concept ElevatorConceptConstPrivate = requires(const E elevator, const P passenger) {
	{ elevator.DoorsOpen() } -> std::convertible_to<bool>;
	{ elevator.Idle() } -> std::convertible_to<bool>;
	{ elevator.GoingDown() } -> std::convertible_to<bool>;
	{ elevator.GoingUp() } -> std::convertible_to<bool>;
	{ elevator.Stopped() } -> std::convertible_to<bool>;
	{ elevator.Active() } -> std::convertible_to<bool>;
	{ elevator.OpenDoors() } -> std::convertible_to<E>;
	{ elevator.CloseDoors() } -> std::convertible_to<E>;
	{ elevator.GoDown() } -> std::convertible_to<E>;
	{ elevator.GoUp() } -> std::convertible_to<E>;
	{ elevator.Stop() } -> std::convertible_to<E>;
	{ elevator.Activate() } -> std::convertible_to<E>;
};


template <
	typename E, typename P,
	typename ActiveStateType, typename DoorStateType, typename HeadingType
>
concept ElevatorConcept =
ElevatorConceptConstPublic<E, P> &&
ElevatorConceptPublic<E, P> &&
ElevatorConceptConstProtected<E, P, ActiveStateType, DoorStateType, HeadingType> &&
ElevatorConceptProtected<E> &&
ElevatorConceptConstPrivate<E, P>;

//template<typename E>
//concept ElevatorConceptPrivate

// Example: Immutable Object Pattern + Friend Class + Concept
// Extended Example: Immutable Object with Protected and Private Members, Friend Class, Concepts, and constexpr
#endif // ELEVATOR_CONCEPTS_H