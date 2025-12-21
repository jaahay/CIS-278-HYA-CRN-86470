#include "elevator/Elevator.h"

constexpr Elevator::Elevator(
    int doorDelayMs,
    int moveDelayMs,
    int current
) :
    doorDelayMs(doorDelayMs),
    moveDelayMs(moveDelayMs),
    current(current),
    opsState(IDLE),
    doorState(DOORS_OPEN),
    heading(STOPPED),
    pendingPassengers(),
    boardedPassengers() {
};
constexpr Elevator::Elevator(
    const int doorDelayMs,
    const int moveDelayMs,
    const int current,
    const std::unique_ptr<OpsStateType> opsState,
    const std::unique_ptr<DoorStateType> doorState,
    const std::unique_ptr<HeadingType> heading,
    const std::list<const PassengerType*> pendingPassengers,
    const std::list<const PassengerType*> boardedPassengers
)
    : doorDelayMs(doorDelayMs)
    , moveDelayMs(moveDelayMs)
    , current(current)
    , opsState(std::move(opsState))
    , doorState(std::move(doorState))
    , heading(std::move(heading))
    , pendingPassengers(std::move(pendingPassengers))
    , boardedPassengers(std::move(boardedPassengers))
{
};

constexpr double Elevator::Divergence(const PassengerType& passenger) const {
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

constexpr Elevator& Elevator::Idle() const
{
    return *opsState == IDLE;
}
template <
    typename PassengerType,
    typename OpsStateType,
    typename DoorStateType,
    typename HeadingType
>
constexpr std::future<std::list<const PassengerType*>> Elevator::ReceivePassenger(const PassengerType& passenger) const {
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


constexpr std::future<bool> Elevator::Wait() const {
    return std::async(
        std::launch::deferred,
        [&]() {
            const std::lock_guard<std::mutex> lock(active);
            return true;
        }
    );
};


constexpr bool Elevator::PassedOrigin(const PassengerType& passenger) const {
    if (Stopped()) { return false; }
    return GoingDown() && passenger.Origin() > current || GoingUp() && passenger.Origin() < current;
}

constexpr bool Elevator::GoingDown() const
{
    return *heading == GOING_DOWN;
}

constexpr bool Elevator::GoingUp() const
{
    return *heading == GOING_UP;
}

constexpr bool Elevator::Stopped() const
{
    return *heading == STOPPED;
}

constexpr bool Elevator::PassedDestination(const PassengerType& passenger) const {
    if (Stopped()) { return false; }
    return GoingDown()  && passenger.Destination() > current || GoingUp() && passenger.Destination() < current;
};

constexpr double Elevator::FarthestToGo() const {
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


constexpr bool Elevator::FurtherToGo() const {
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


constexpr bool Elevator::Board() const {
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

constexpr Elevator& Elevator::Stop() const
{

    heading = std::make_unique<OpsState>(STOPPED);
    opsState = std::make_unique<OpsState>(IDLE);
    std::cout << "Elevator has come to a halt." << std::endl;
    heading = STOPPED;
    return *this;
}

constexpr Elevator& Elevator::OpenDoors() const
{
    doorState = DOORS_OPENING;
    std::cout << "Doors opening..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(doorDelayMs)); // Simulate door opening time
    doorState = DOORS_OPEN;
    return *this;
}

constexpr bool Elevator::DoorsOpen() const
{
    return *doorState == DOORS_OPEN;
}

constexpr Elevator& Elevator::CloseDoors() const
{
    doorState = &DOORS_CLOSING;
    std::this_thread::sleep_for(std::chrono::milliseconds(doorDelayMs)); // Simulate door closing time
    doorState = &DOORS_CLOSED;
    std::cout << "Doors closed." << std::endl;
    return *this;
}

constexpr Elevator& Elevator::GoDown() const
{
    heading.reset(&GOING_DOWN);
    return *this;
}

constexpr Elevator& Elevator::GoUp() const
{
    heading = std::make_unique<Heading>(GOING_UP);
    return *this;
}

constexpr void Elevator::MoveLoop() const {
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

constexpr bool Elevator::Active() const
{
    return *opsState == ACTIVE;
}

constexpr Elevator& Elevator::Activate() const
{
    opsState = &ACTIVE;
    return *this;
}

/**
 * not thread safe.
 */
constexpr void Elevator::Move() const {
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

std::ostream& operator<<(std::ostream& os, const Elevator& elevator) {
    os << "Currently at floor " << elevator.current << ". ";
    os << elevator.opsState << " " << elevator.doorState << " " << elevator.heading << ".";

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