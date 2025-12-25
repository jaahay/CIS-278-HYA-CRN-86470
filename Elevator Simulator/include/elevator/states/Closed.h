// elevator/states/Closed.h
#ifndef ELEVATOR_STATES_CLOSED_H
#define ELEVATOR_STATES_CLOSED_H

#include "core/state/TemplateState.h"
#include "elevator/states/ElevatorStateTypes.h"

namespace elevator::states {

    struct Closed : core::state::TemplateState<Closed, DoorState> {
    private:
        Closed() = default;

    public:
        Closed(const Closed&) = delete;
        Closed& operator=(const Closed&) = delete;
        Closed(Closed&&) = delete;
        Closed& operator=(Closed&&) = delete;

        constexpr bool IsOpened() const { return false; }
        constexpr bool IsClosed() const { return true;  }

        constexpr std::string_view name() const noexcept { return "Closed"; }

        void print(std::ostream& os) const noexcept override {
            os << name();
        }

        [[nodiscard]] static const Closed& instance() noexcept {
            static const Closed instance;
            return instance;
        }
    };

} // namespace elevator::states

#endif // ELEVATOR_STATES_CLOSED_H
