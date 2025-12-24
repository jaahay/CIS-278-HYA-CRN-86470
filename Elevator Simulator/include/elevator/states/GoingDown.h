// elevator/states/GoingDown.h
#ifndef ELEVATOR_STATES_GOING_DOWN_H
#define ELEVATOR_STATES_GOING_DOWN_H

#include "elevator/states/ElevatorStateTypes.h"

namespace elevator::states {

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

        constexpr std::string_view name() const noexcept { return "Going Down"; }

        void print(std::ostream& os) const noexcept override {
            os << name();
        }

        [[nodiscard]] static const GoingDown& instance() noexcept {
            static const GoingDown instance;
            return instance;
        }
    };

} // namespace elevator::states

#endif // ELEVATOR_STATES_GOING_DOWN_H
