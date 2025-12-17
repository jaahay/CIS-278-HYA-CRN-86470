#include <algorithm>
#include "Elevator.h"

const double Elevator::Divergence(const Passenger& passenger) const {
    // std::cout << "Check ";
    // passenger.print(std::cout);

    if (heading == STOPPED) {
        if (current == passenger.Origin() && doorState == DOORS_OPEN &&
            (*state == IDLE || heading == passenger.Heading())
            ) {
            return 0;
        }

        if (*state == IDLE) {
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
};

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
    if (elevator.heading == STOPPED) { return false; }
    return elevator.heading == GOING_DOWN && passenger.Origin() > elevator.current || elevator.heading == GOING_UP && passenger.Origin() < elevator.current;
};

const bool Elevator::PassedDestination(const Elevator& elevator, const Passenger& passenger) const {
    if (elevator.heading == STOPPED) { return false; }
    return elevator.heading == GOING_DOWN && passenger.Destination() > elevator.current || elevator.heading == GOING_UP && passenger.Destination() < elevator.current;
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
    if (elevator.heading == GOING_UP) {
        return *std::max_element(forwardStops.begin(), forwardStops.end());
    }
    else {
        return *std::min_element(forwardStops.begin(), forwardStops.end());
    }
    return 0;
};

const bool Elevator::FurtherToGo(const Elevator& elevator) const {
    if (elevator.heading == STOPPED) { return false; }
    if (elevator.boardedPassengers.empty()) {
        for (const auto& pendingPassenger : elevator.pendingPassengers) {
            if (elevator.heading != pendingPassenger->Heading()) { continue; }
            if (elevator.heading == GOING_UP && pendingPassenger->Origin() > elevator.current) { return true; }
            if (elevator.heading == GOING_DOWN && pendingPassenger->Origin() < elevator.current) { return true; }
        }
    }
    for (const auto& boardedPassenger : elevator.boardedPassengers) {
        if (elevator.heading == GOING_UP && boardedPassenger->Destination() > elevator.current) { return true; }
        if (elevator.heading == GOING_DOWN && boardedPassenger->Destination() < elevator.current) { return true; }
    }
    return false;
};

const bool Elevator::Board(Elevator& elevator) {
    bool board = false;
    if (!elevator.pendingPassengers.empty()) {
        for (auto passenger = elevator.pendingPassengers.begin(); passenger != elevator.pendingPassengers.end();) {
            if (elevator.current == (*passenger)->Origin() && (elevator.heading == STOPPED || elevator.heading == (*passenger)->Heading())) {
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

const void Elevator::MoveLoop(Elevator& elevator) {
    bool board = Board(elevator);
    bool depart = Leave(elevator);

    if (elevator.pendingPassengers.empty() && elevator.boardedPassengers.empty()) {
        elevator.heading = STOPPED;
    }

    if (board || depart) {
        std::cout << "An elevator is currently servicing floor " << elevator.current << std::endl;
        std::cout << elevator << std::endl;
        elevator.doorState = DOORS_OPENING;
        std::cout << "Doors opening..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(elevator.doorDelay)); // Simulate door opening time
        elevator.doorState = DOORS_OPEN;
    }

    if (elevator.pendingPassengers.empty() && elevator.boardedPassengers.empty()) {
        elevator.state = &IDLE;
        std::cout << "Elevator has come to a halt." << std::endl;
    }
    else if (elevator.doorState == DOORS_OPEN) {
        elevator.doorState = DOORS_CLOSING;
        std::this_thread::sleep_for(std::chrono::milliseconds(elevator.doorDelay)); // Simulate door closing time
        elevator.doorState = DOORS_CLOSED;
        std::cout << "Doors closed." << std::endl;
    }
    else if (!FurtherToGo(elevator)) {
        elevator.heading = elevator.heading == GOING_UP ? GOING_DOWN : GOING_UP;
    }

    if (elevator.heading == GOING_UP) {
        std::this_thread::sleep_for(std::chrono::milliseconds(elevator.moveDelay)); // Simulate time taken to move one floor
        ++elevator.current;
    }
    if (elevator.heading == GOING_DOWN) {
        std::this_thread::sleep_for(std::chrono::milliseconds(elevator.moveDelay)); // Simulate time taken to move one floor
        --elevator.current;
    }
};

/**
 * not thread safe.
 */
const void Elevator::Move(Elevator& elevator) {
    if (*(elevator.state) == ACTIVE) { return; }
    std::thread t([&]() {
        const std::lock_guard<std::mutex> lock(elevator.active);
        elevator.state = &ACTIVE;
        while (!elevator.pendingPassengers.empty() || !elevator.boardedPassengers.empty()) {
            MoveLoop(elevator);
        }
        });
    t.detach();
};