// elevator/detail/DoorsClosing.h
#ifndef ELEVATOR_DETAIL_DOORS_CLOSING_H
#define ELEVATOR_DETAIL_DOORS_CLOSING_H

#include "DoorState.h"

namespace elevator::detail {

    struct DoorsClosing : core::TemplateState<DoorsClosing, DoorState> {
    private:
        DoorsClosing() = default;

    public:
        DoorsClosing(const DoorsClosing&) = delete;
        DoorsClosing& operator=(const DoorsClosing&) = delete;
        DoorsClosing(DoorsClosing&&) = delete;
        DoorsClosing& operator=(DoorsClosing&&) = delete;

        constexpr std::string_view name() const noexcept { return "Doors Closing"; }

        void print(std::ostream& os) const noexcept override {
            os << name();
        }

        [[nodiscard]] static const DoorsClosing& instance() noexcept {
            static const DoorsClosing instance;
            return instance;
        }
    };

} // namespace elevator::detail

#endif // ELEVATOR_DETAIL_DOORS_CLOSING_H
