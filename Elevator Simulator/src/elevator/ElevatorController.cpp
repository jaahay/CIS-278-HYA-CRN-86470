// elevator/ElevatorController.cpp
#include "elevator/ElevatorController.h"

namespace elevator {

    ElevatorController::ElevatorController(Elevator initialElevator)
        : elevator(std::move(initialElevator))
    {
    }

    std::future<Elevator> ElevatorController::AddPassenger(const Passenger& passenger) {
        std::lock_guard lock(mutex);
        busy = true;

        // Call Elevator::ReceivePassenger asynchronously
        auto fut = elevator.ReceivePassenger(passenger);

        return std::async(std::launch::async, [this, fut = std::move(fut)]() mutable {
            Elevator updated = fut.get();
            {
                std::lock_guard lock(mutex);
                elevator = std::move(updated);
                busy = false;
            }
            cv.notify_all();
            return elevator;
            });
    }

    std::future<Elevator> ElevatorController::Move() {
        std::lock_guard lock(mutex);
        busy = true;

        auto fut = elevator.MoveAsync();

        return std::async(std::launch::async, [this, fut = std::move(fut)]() mutable {
            Elevator updated = fut.get();
            {
                std::lock_guard lock(mutex);
                elevator = std::move(updated);
                busy = false;
            }
            cv.notify_all();
            return elevator;
            });
    }

    void ElevatorController::Wait() {
        std::unique_lock lock(mutex);
        cv.wait(lock, [this]() { return !busy; });
    }

    Elevator ElevatorController::GetElevator() const {
        std::lock_guard lock(mutex);
        return elevator;
    }

    void ElevatorController::setBusy(bool busy) {
        busy = busy;
        cv.notify_all();
    }

} // namespace elevator
