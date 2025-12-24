// elevator/states/Opening.h
#ifndef ELEVATOR_STATES_DETAILS_OPENING_H
#define ELEVATOR_STATES_DETAILS_OPENING_H

#include "elevator/states/ElevatorStateTypes.h"

namespace elevator::states {

    struct Opening : core::TemplateState<Opening, DoorState> {
    private:
        Opening() = default;

    public:
        Opening(const Opening&) = delete;
        Opening& operator=(const Opening&) = delete;
        Opening(Opening&&) = delete;
        Opening& operator=(Opening&&) = delete;

        constexpr bool Opened() const { return false; }
        constexpr bool Closed() const { return false; }

        constexpr std::string_view name() const noexcept { return "Opening"; }

        void print(std::ostream& os) const noexcept override {
            os << name();
        }

        [[nodiscard]] static const Opening& instance() noexcept {
            static const Opening instance;
            return instance;
        }
    };

} // namespace elevator::states

#endif // ELEVATOR_STATES_DETAILS_OPENING_H
