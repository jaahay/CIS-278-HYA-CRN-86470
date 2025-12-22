// elevator/ElevatorController.h
#ifndef ELEVATOR_CONTROLLER_H
#define ELEVATOR_CONTROLLER_H

#include "Elevator.h"
#include <mutex>
#include <condition_variable>
#include <atomic>

namespace elevator {

    class ElevatorController {
    public:
        ElevatorController(Elevator initialElevator);

        // Add passenger, returns future of updated Elevator
        std::future<Elevator> AddPassenger(const Passenger& passenger);

        // Request elevator to move asynchronously
        std::future<Elevator> Move();

        // Wait until elevator is idle or operation completes
        void Wait();

        // Get current Elevator state (thread-safe)
        Elevator GetElevator() const;

    private:
        mutable std::mutex mutex;
        mutable std::condition_variable cv;
        Elevator elevator;
        std::atomic<bool> busy = false;

        void setBusy(bool busy);
    };

} // namespace elevator

#endif // ELEVATOR_CONTROLLER_H