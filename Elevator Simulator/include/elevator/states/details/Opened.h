// elevator/states/details/Opened.h
#ifndef ELEVATOR_STATES_DETAILS_OPENED_H
#define ELEVATOR_STATES_DETAILS_OPENED_H

#include "elevator/states/Types.h"

namespace elevator::states::details {

    struct Opened : core::TemplateState<Opened, DoorState> {
    private:
        Opened() = default;

    public:
        Opened(const Opened&) = delete;
        Opened& operator=(const Opened&) = delete;
        Opened(Opened&&) = delete;
        Opened& operator=(Opened&&) = delete;

        constexpr bool Opened() const { return true; }
        constexpr bool Closed() const { return false; }

        constexpr std::string_view name() const noexcept { return "Opened"; }

        void print(std::ostream& os) const noexcept override {
            os << name();
        }

        [[nodiscard]] static const Opened& instance() noexcept {
            static const Opened instance;
            return instance;
        }
    };

} // namespace elevator::states::details

#endif // ELEVATOR_STATES_DETAILS_OPENED_H
