// elevator/services/ElevatorService.h
#ifndef ELEVATOR_SERVICES_ELEVATOR_SERVICE_H
#define ELEVATOR_SERVICES_ELEVATOR_SERVICE_H

#include <future>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <list>
#include "elevator/models/Elevator.h"
#include "core/Core.h"

namespace elevator::services {

    class ElevatorService {
    public:
        ElevatorService();

        // Add a passenger asynchronously
        std::future<Elevator> AddPassenger(const Passenger& passenger);

        // Move elevator asynchronously (one step)
        std::future<Elevator> Move();

        // Wait until elevator is idle or not busy (with timeout)
        void Wait(std::chrono::milliseconds timeout = std::chrono::seconds(10));

        // Get current elevator state (thread-safe)
        Elevator GetElevator() const;

        // Observer management
        ObserverId AddObserver(core::StateChangeCallback<const core::detail::StateChangeEvent<ElevatorStateVariant>&> observer);
        bool RemoveObserver(ObserverId id);

    private:
        mutable std::mutex mutex_;
        std::condition_variable cv_;
        std::atomic<bool> busy_;

        Elevator elevator_;

        core::event::Dispatcher<const core::detail::StateChangeEvent<ElevatorStateVariant>&> dispatcher_;

        // Internal synchronous move step performing full elevator logic
        Elevator PerformMoveStep();

        // Helper to update elevator state safely and notify observers
        void UpdateElevatorState(const Elevator& newElevator);
    };

} // namespace elevator::services

#endif // ELEVATOR_SERVICES_ELEVATOR_SERVICE_H
