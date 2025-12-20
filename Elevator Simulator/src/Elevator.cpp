#include <algorithm>
#include "Elevator.h"


template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr bool Elevator<E, P>::IsIdle() const { return *state == IDLE; }

template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr double Elevator<E, P>::Divergence(const P& passenger) const {
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
template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr E& Elevator<E, P>::Idle() const
{
    return *state == IDLE;
}
template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr std::future<std::list<const P*>> Elevator<E, P>::ReceivePassenger(const P& passenger) const {
    return std::async(
        std::launch::async,
        [this](const Passenger &passenger) {
            if (pendingPassengers.end() == std::find(pendingPassengers.begin(), pendingPassengers.end(), &passenger)) {
                std::cout << "Passenger request " << passenger << " received." << std::endl;
                pendingPassengers.insert(pendingPassengers.end(), &passenger);
                std::cout << passenger << std::endl;
                Move();
            }
            return pendingPassengers;
        },
        std::ref(passenger)
    );
};

template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr std::future<bool> Elevator<E, P>::Wait() const {
    return std::async(
        std::launch::deferred,
        [&]() {
            const std::lock_guard<std::mutex> lock(active);
            return true;
        }
    );
};

template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr bool Elevator<E, P>::PassedOrigin(const P& passenger) const {
    if (Stopped()) { return false; }
    return GoingDown() && passenger.Origin() > current || GoingUp() && passenger.Origin() < current;
}
template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr bool Elevator<E, P>::GoingDown() const
{
    return *heading == GOING_DOWN;
}
template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr bool Elevator<E, P>::GoingUp() const
{
    return *heading == GOING_UP;
}
template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr bool Elevator<E, P>::Stopped() const
{
    return *heading == STOPPED;
}
template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr bool Elevator<E, P>::PassedDestination(const P& passenger) const {
    if (Stopped()) { return false; }
    return GoingDown()  && passenger.Destination() > current || GoingUp() && passenger.Destination() < current;
};
template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr double Elevator<E, P>::FarthestToGo() const {
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
    if (GoingUp()) {
        return *std::max_element(forwardStops.begin(), forwardStops.end());
    }
    else {
        return *std::min_element(forwardStops.begin(), forwardStops.end());
    }
    return 0;
};
template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr bool Elevator<E, P>::FurtherToGo() const {
    if (Stopped()) { return false; }
    if (boardedPassengers.empty()) {
        for (const auto& pendingPassenger : pendingPassengers) {
            if (!pendingPassenger->GoingMyWay(*heading)) { continue; }
            if (GoingUp()  && pendingPassenger->Origin() > current) { return true; }
            if (GoingDown()  && pendingPassenger->Origin() < current) { return true; }
        }
    }
    for (const auto& boardedPassenger : boardedPassengers) {
        if (GoingUp()  && boardedPassenger->Destination() > current) { return true; }
        if (GoingDown()  && boardedPassenger->Destination() < current) { return true; }
    }
    return false;
};
template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr bool Elevator<E, P>::Board() const {
    bool board = false;
    if (!pendingPassengers.empty()) {
        for (auto passenger = pendingPassengers.begin(); passenger != pendingPassengers.end();) {
            if (current == (*passenger)->Origin() && (Stopped() || (*passenger)->GoingMyWay(*(heading)))) {
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
template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr bool Elevator<E, P>::Leave() const {
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
template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr E& Elevator<E, P>::Stop() const
{

    heading = std::make_unique<ActiveState>(STOPPED);
    state = std::make_unique<ActiveState>(IDLE);
    std::cout << "Elevator has come to a halt." << std::endl;
    heading = STOPPED;
    return *this;
}
template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr E& Elevator<E, P>::OpenDoors() const
{
    doorState = DOORS_OPENING;
    std::cout << "Doors opening..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(doorDelayMs)); // Simulate door opening time
    doorState = DOORS_OPEN;
    return *this;
}
template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr bool Elevator<E, P>::DoorsOpen() const
{
    return *doorState == DOORS_OPEN;
}
template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr E& Elevator<E, P>::CloseDoors() const
{
    doorState = &DOORS_CLOSING;
    std::this_thread::sleep_for(std::chrono::milliseconds(doorDelayMs)); // Simulate door closing time
    doorState = &DOORS_CLOSED;
    std::cout << "Doors closed." << std::endl;
    return *this;
}
template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr E& Elevator<E, P>::GoDown() const
{
    heading.reset(&GOING_DOWN);
    return *this;
}
template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr E& Elevator<E, P>::GoUp() const
{
    heading = std::make_unique<Heading>(GOING_UP);
    return *this;
}
template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr void Elevator<E, P>::MoveLoop() const {
    bool board = Board();
    bool depart = Leave();

    /*if (elevator.pendingPassengers.empty() && elevator.boardedPassengers.empty()) {
        elevator.Stop();
    }*/

    if (board || depart) {
        std::cout << "An elevator is currently servicing floor " << current << std::endl;
        std::cout << this << std::endl;
        OpenDoors();    
    }

    if (pendingPassengers.empty() && boardedPassengers.empty()) {
        Stop();
    }
    else if (DoorsOpen()) {
        CloseDoors();
    }
    else if (!FurtherToGo()) {
        if (GoingUp()) {
            GoDown();
        }
        else {
            GoUp();
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(moveDelayMs)); // Simulate time taken to move one floor
    if (GoingUp()) {
        ++current;
    }
    if (GoingDown()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(moveDelayMs)); // Simulate time taken to move one floor
        --current;
    }
};
template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr bool Elevator<E, P>::Active() const
{
    return *state == ACTIVE;
}
template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr E& Elevator<E, P>::Activate() const
{
    state = &ACTIVE;
    return *this;
}

/**
 * not thread safe.
 */
template<typename E, typename P>
    requires ElevatorConcept<E, P>
constexpr void Elevator<E, P>::Move() const {
    if (Active()) { return; }
    std::thread t([&]() {
        const std::lock_guard<std::mutex> lock(active);
        Activate();
        while (!pendingPassengers.empty() || !boardedPassengers.empty()) {
            MoveLoop();
        }
        });
    t.detach();
};
template<typename E, typename P>
    requires ElevatorConcept<E, P>
std::ostream& operator<<(std::ostream& os, const E& elevator) {
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