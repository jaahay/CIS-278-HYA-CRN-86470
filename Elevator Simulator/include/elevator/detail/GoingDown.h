// elevator/detail/GoingDown.h
#ifndef ELEVATOR_DETAIL_GOING_DOWN_H
#define ELEVATOR_DETAIL_GOING_DOWN_H

#include "elevator/detail/DomainState.h"

namespace elevator::detail {

    struct GoingDown : core::TemplateState<GoingDown, Heading> {
    private:
        GoingDown() = default;

    public:
        GoingDown(const GoingDown&) = delete;
        GoingDown& operator=(const GoingDown&) = delete;
        GoingDown(GoingDown&&) = delete;
        GoingDown& operator=(GoingDown&&) = delete;

        bool IsStopped() const override { return false; }
        bool IsGoingUp() const override { return false; }
        bool IsGoingDown() const override { return true; }

        //bool PassedOrigin(const Elevator& elevator, const Passenger& passenger) const override {
        //    return passenger.Destination() > elevator.CurrentFloor();
        //}

        //bool PassedDestination(const Elevator& elevator, const Passenger& passenger) const override {
        //    return passenger.Destination() > elevator.CurrentFloor();
        //}

        constexpr std::string_view name() const noexcept { return "Going Down"; }

        void print(std::ostream& os) const noexcept override {
            os << name();
        }

        [[nodiscard]] static const GoingDown& instance() noexcept {
            static const GoingDown instance;
            return instance;
        }
    };

} // namespace elevator::detail

#endif // ELEVATOR_DETAIL_GOING_DOWN_H
