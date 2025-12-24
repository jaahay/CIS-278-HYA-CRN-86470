// elevator/states/Opened.h
#ifndef ELEVATOR_STATES_OPENED_H
#define ELEVATOR_STATES_OPENED_H

#include "elevator/states/ElevatorStateTypes.h"

namespace elevator::states {

    struct Opened : core::TemplateState<Opened, DoorState> {
    private:
        Opened() = default;

    public:
        Opened(const Opened&) = delete;
        Opened& operator=(const Opened&) = delete;
        Opened(Opened&&) = delete;
        Opened& operator=(Opened&&) = delete;

        constexpr bool IsOpened() const { return true; }
        constexpr bool IsClosed() const { return false; }

        constexpr std::string_view name() const noexcept { return "Opened"; }

        void print(std::ostream& os) const noexcept override {
            os << name();
        }

        [[nodiscard]] static const Opened& instance() noexcept {
            static const Opened instance;
            return instance;
        }
    };

} // namespace elevator::states

#endif // ELEVATOR_STATES_OPENED_H
