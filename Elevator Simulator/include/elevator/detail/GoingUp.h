// elevator/detail/GoingUp.h
#ifndef ELEVATOR_DETAIL_GOING_UP_H
#define ELEVATOR_DETAIL_GOING_UP_H

#include "Heading.h"

namespace elevator::detail {

    struct GoingUp : core::TemplateState<GoingUp, Heading> {
    private:
        GoingUp() = default;

    public:
        GoingUp(const GoingUp&) = delete;
        GoingUp& operator=(const GoingUp&) = delete;
        GoingUp(GoingUp&&) = delete;
        GoingUp& operator=(GoingUp&&) = delete;

        bool IsStopped() const override { return false; }
        bool IsGoingUp() const override { return true; }
        bool IsGoingDown() const override { return false; }

        bool PassedOrigin(const Elevator& elevator, const Passenger& passenger) const override {
            return passenger.Origin() < elevator.CurrentFloor();
        }

        bool PassedDestination(const Elevator& elevator, const Passenger& passenger) const override {
            return passenger.Destination() < elevator.CurrentFloor();
        }

        constexpr std::string_view name() const noexcept { return "Going Up"; }

        void print(std::ostream& os) const noexcept override {
            os << name();
        }

        [[nodiscard]] static const GoingUp& instance() noexcept {
            static const GoingUp instance;
            return instance;
        }
    };

} // namespace elevator::detail

#endif // ELEVATOR_DETAIL_GOING_UP_H
