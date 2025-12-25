// elevator/states/Idle.h
#ifndef ELEVATOR_STATES_IDLE_H
#define ELEVATOR_STATES_IDLE_H

#include "core/state/TemplateState.h"
#include "elevator/states/ElevatorStateTypes.h"

namespace elevator::states {

    struct Idle : core::state::TemplateState<Idle, OperationState> {
    private:
        Idle() = default;

    public:
        Idle(const Idle&) = delete;
        Idle& operator=(const Idle&) = delete;
        Idle(Idle&&) = delete;
        Idle& operator=(Idle&&) = delete;

        constexpr bool IsActive() const override { return false;  }

        constexpr std::string_view name() const noexcept { return "Idle"; }

        void print(std::ostream& os) const noexcept override {
            os << name();
        }

        [[nodiscard]] static const Idle& instance() noexcept {
            static const Idle instance;
            return instance;
        }
    };

} // namespace elevator::states

#endif // ELEVATOR_STATES_IDLE_H
