// elevator/states/Closing.h
#ifndef ELEVATOR_STATES_CLOSING_H
#define ELEVATOR_STATES_CLOSING_H

#include "core/state/TemplateState.h"
#include "elevator/states/ElevatorStateTypes.h"

namespace elevator::states {

    struct Closing : core::state::TemplateState<Closing, DoorState> {
    private:
        Closing() = default;

    public:
        Closing(const Closing&) = delete;
        Closing& operator=(const Closing&) = delete;
        Closing(Closing&&) = delete;
        Closing& operator=(Closing&&) = delete;

        constexpr bool IsOpened() const { return false; }
        constexpr bool IsClosed() const { return false; }

        constexpr std::string_view name() const noexcept { return "Closing"; }

        void print(std::ostream& os) const noexcept override {
            os << name();
        }

        [[nodiscard]] static const Closing& instance() noexcept {
            static const Closing instance;
            return instance;
        }
    };

} // namespace elevator::states

#endif // ELEVATOR_STATES_CLOSING_H
