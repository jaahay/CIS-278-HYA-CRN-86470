#include <algorithm>
#include "Elevator.h"

const double Elevator::Divergence(const Passenger& passenger) const {
    // std::cout << "Check ";
    // passenger.print(std::cout);

    if (Stopped()) {
        if (current == passenger.Origin() && DoorsOpen() &&
            (Idle() || heading == passenger.Heading())
            ) {
            return 0;
        }

        if (Idle()) {
            return std::abs(current - passenger.Origin());
        }
    }

    if (heading == passenger.Heading()) {
        if (PassedOrigin(*this, passenger)) {
            return 2 * std::abs(current - FarthestToGo(*this)) + std::abs(current - passenger.Origin());
        }
        else {
            return std::abs(current - passenger.Origin());
        }
    }

    if (heading != passenger.Heading()) {
        double f = FarthestToGo(*this);
        return std::abs(f - current) + std::abs(f - passenger.Origin());
    }

    throw std::invalid_argument("Invalid heading for elevator.");
}
bool Elevator::Idle() const
{
    return *state == IDLE;
}

const std::future<std::list<const Passenger*>> Elevator::ReceivePassenger(const Passenger& passenger) {
    return std::async(
        std::launch::async,
        [this](const Passenger &passenger) {
            if (pendingPassengers.end() == std::find(pendingPassengers.begin(), pendingPassengers.end(), &passenger)) {
                std::cout << "Passenger request " << passenger << " received." << std::endl;
                pendingPassengers.insert(pendingPassengers.end(), &passenger);
                std::cout << passenger << std::endl;
                Move(*this);
            }
            return pendingPassengers;
        },
        std::ref(passenger)
    );
};

const std::future<bool> Elevator::Wait() {
    return std::async(
        std::launch::deferred,
        [&]() {
            const std::lock_guard<std::mutex> lock(active);
            return true;
        }
    );
};

const bool Elevator::PassedOrigin(const Elevator& elevator, const Passenger& passenger) const {
    if (elevator.Stopped()) { return false; }
    return elevator.GoingDown() && passenger.Origin() > elevator.current || elevator.GoingUp() && passenger.Origin() < elevator.current;
}
bool Elevator::GoingDown() const
{
    return heading == &GOING_DOWN;
}
bool Elevator::GoingUp() const
{
    return heading == &GOING_UP;
}
bool Elevator::Stopped() const
{
    return heading == &STOPPED;
}

const bool Elevator::PassedDestination(const Elevator& elevator, const Passenger& passenger) const {
    if (elevator.Stopped()) { return false; }
    return elevator.GoingDown()  && passenger.Destination() > elevator.current || elevator.GoingUp() && passenger.Destination() < elevator.current;
};

const double Elevator::FarthestToGo(const Elevator& elevator) const {
    std::list<double> forwardStops;
    for (const auto& pendingPassenger : elevator.pendingPassengers) {
        if (!PassedOrigin(elevator, *pendingPassenger)) {
            forwardStops.push_back(pendingPassenger->Origin());
        }
    }
    for (const auto& boardedPassenger : elevator.boardedPassengers) {
        if (!PassedDestination(elevator, *boardedPassenger)) {
            forwardStops.push_back(boardedPassenger->Destination());
        }
    }
    if (elevator.GoingUp()) {
        return *std::max_element(forwardStops.begin(), forwardStops.end());
    }
    else {
        return *std::min_element(forwardStops.begin(), forwardStops.end());
    }
    return 0;
};

const bool Elevator::FurtherToGo(const Elevator& elevator) const {
    if (elevator.Stopped()) { return false; }
    if (elevator.boardedPassengers.empty()) {
        for (const auto& pendingPassenger : elevator.pendingPassengers) {
            if (elevator.heading != pendingPassenger->Heading()) { continue; }
            if (elevator.GoingUp()  && pendingPassenger->Origin() > elevator.current) { return true; }
            if (elevator.GoingDown()  && pendingPassenger->Origin() < elevator.current) { return true; }
        }
    }
    for (const auto& boardedPassenger : elevator.boardedPassengers) {
        if (elevator.GoingUp()  && boardedPassenger->Destination() > elevator.current) { return true; }
        if (elevator.GoingDown()  && boardedPassenger->Destination() < elevator.current) { return true; }
    }
    return false;
};

const bool Elevator::Board(Elevator& elevator) {
    bool board = false;
    if (!elevator.pendingPassengers.empty()) {
        for (auto passenger = elevator.pendingPassengers.begin(); passenger != elevator.pendingPassengers.end();) {
            if (elevator.current == (*passenger)->Origin() && (elevator.Stopped() || elevator.heading == (*passenger)->Heading())) {
                std::cout << "Passenger " << *passenger << " is boarding. " << std::endl;
                elevator.boardedPassengers.push_back(*passenger);
                passenger = elevator.pendingPassengers.erase(passenger);
                board = true;
            }
            else {
                ++passenger;
            }
        }
    }
    return board;
};

const bool Elevator::Leave(Elevator& elevator) {
    bool leave = false;
    if (!elevator.boardedPassengers.empty()) {
        for (auto boardedPassenger = elevator.boardedPassengers.begin(); boardedPassenger != elevator.boardedPassengers.end();) {
            if (elevator.current == (*boardedPassenger)->Destination()) {
                std::cout << std::endl << "Passenger " << *boardedPassenger << " is leaving." << std::endl;
                boardedPassenger = elevator.boardedPassengers.erase(boardedPassenger);
                leave = true;
            }
            else {
                ++boardedPassenger;
            }
        }
    }
    return leave;
};

Elevator& Elevator::Stop()
{
    heading = &STOPPED;
    state = &IDLE;
    std::cout << "Elevator has come to a halt." << std::endl;
    heading = &STOPPED;
    return *this;
}

Elevator& Elevator::OpenDoors()
{
    doorState = &DOORS_OPENING;
    std::cout << "Doors opening..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(doorDelay)); // Simulate door opening time
    doorState = &DOORS_OPEN;
    return *this;
}

bool Elevator::DoorsOpen() const
{
    return *doorState == DOORS_OPEN;
}

Elevator& Elevator::CloseDoors()
{
    doorState = &DOORS_CLOSING;
    std::this_thread::sleep_for(std::chrono::milliseconds(doorDelay)); // Simulate door closing time
    doorState = &DOORS_CLOSED;
    std::cout << "Doors closed." << std::endl;
    return *this;
}

Elevator& Elevator::GoDown()
{
    heading = &GOING_DOWN;
    return *this;
}

Elevator& Elevator::GoUp()
{
    heading = &GOING_UP;
    return *this;
}

const void Elevator::MoveLoop(Elevator& elevator) {
    bool board = Board(elevator);
    bool depart = Leave(elevator);

    /*if (elevator.pendingPassengers.empty() && elevator.boardedPassengers.empty()) {
        elevator.Stop();
    }*/

    if (board || depart) {
        std::cout << "An elevator is currently servicing floor " << elevator.current << std::endl;
        std::cout << elevator << std::endl;
        elevator.OpenDoors();    
    }

    if (elevator.pendingPassengers.empty() && elevator.boardedPassengers.empty()) {
        elevator.Stop();
    }
    else if (elevator.DoorsOpen()) {
        elevator.CloseDoors();
    }
    else if (!FurtherToGo(elevator)) {
        if (elevator.GoingUp()) {
            elevator.GoDown();
        }
        else {
            elevator.GoUp();
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(elevator.moveDelay)); // Simulate time taken to move one floor
    if (elevator.GoingUp()) {
        ++elevator.current;
    }
    if (elevator.GoingDown()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(elevator.moveDelay)); // Simulate time taken to move one floor
    }
};

bool Elevator::Active() const
{
    return *state == ACTIVE;
}

Elevator& Elevator::Activate()
{
    state = &ACTIVE;
    return *this;
}

/**
 * not thread safe.
 */
const void Elevator::Move(Elevator& elevator) {
    if (elevator.Active()) { return; }
    std::thread t([&]() {
        const std::lock_guard<std::mutex> lock(elevator.active);
        elevator.Activate();
        while (!elevator.pendingPassengers.empty() || !elevator.boardedPassengers.empty()) {
            MoveLoop(elevator);
        }
        });
    t.detach();
};