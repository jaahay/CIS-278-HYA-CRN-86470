// elevator/detail/DoorsOpening.h
#ifndef ELEVATOR_DETAIL_DOORS_OPENING_H
#define ELEVATOR_DETAIL_DOORS_OPENING_H

#include "DoorState.h"

namespace elevator::detail {

    struct DoorsOpening : core::TemplateState<DoorsOpening, DoorState> {
    private:
        DoorsOpening() = default;

    public:
        DoorsOpening(const DoorsOpening&) = delete;
        DoorsOpening& operator=(const DoorsOpening&) = delete;
        DoorsOpening(DoorsOpening&&) = delete;
        DoorsOpening& operator=(DoorsOpening&&) = delete;

        constexpr std::string_view name() const noexcept { return "Doors Opening"; }

        void print(std::ostream& os) const noexcept override {
            os << name();
        }

        [[nodiscard]] static const DoorsOpening& instance() noexcept {
            static const DoorsOpening instance;
            return instance;
        }
    };

} // namespace elevator::detail

#endif // ELEVATOR_DETAIL_DOORS_OPENING_H
