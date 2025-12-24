// elevator/states/details/Closing.h
#ifndef ELEVATOR_STATES_DETAILS_CLOSING_H
#define ELEVATOR_STATES_DETAILS_CLOSING_H

#include "elevator/states/Types.h"

namespace elevator::states::details {

    struct Closing : core::TemplateState<Closing, DoorState> {
    private:
        Closing() = default;

    public:
        Closing(const Closing&) = delete;
        Closing& operator=(const Closing&) = delete;
        Closing(Closing&&) = delete;
        Closing& operator=(Closing&&) = delete;

        constexpr bool Opened() const { return false; }
        constexpr bool Closed() const { return false; }

        constexpr std::string_view name() const noexcept { return "Closing"; }

        void print(std::ostream& os) const noexcept override {
            os << name();
        }

        [[nodiscard]] static const Closing& instance() noexcept {
            static const Closing instance;
            return instance;
        }
    };

} // namespace elevator::states::details

#endif // ELEVATOR_STATES_DETAILS_CLOSING_H
