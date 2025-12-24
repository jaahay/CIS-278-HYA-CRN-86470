// elevator/models/states/details/GoingUp.h
#ifndef ELEVATOR_MODELS_STATES_DETAILS_GOING_UP_H
#define ELEVATOR_MODELS_STATES_DETAILS_GOING_UP_H

#include "elevator/models/states/Types.h"

namespace elevator::model::states::details {

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

        constexpr std::string_view name() const noexcept { return "Going Up"; }

        void print(std::ostream& os) const noexcept override {
            os << name();
        }

        [[nodiscard]] static const GoingUp& instance() noexcept {
            static const GoingUp instance;
            return instance;
        }
    };

} // namespace elevator::model::states::details

#endif // ELEVATOR_MODELS_STATES_DETAILS_GOING_UP_H
