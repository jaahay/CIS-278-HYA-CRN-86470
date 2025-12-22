// include/elevator/detail/DoorsOpened.h
#ifndef ELEVATOR_DETAIL_DOORS_OPENED_H
#define ELEVATOR_DETAIL_DOORS_OPENED_H

#include "core/TemplateState.h"
#include "DoorState.h"

namespace elevator::detail {

    struct DoorsOpened : core::TemplateState<DoorsOpened, DoorState> {
    private:
        DoorsOpened() = default;

    public:
        DoorsOpened(const DoorsOpened&) = delete;
        DoorsOpened& operator=(const DoorsOpened&) = delete;
        DoorsOpened(DoorsOpened&&) = delete;
        DoorsOpened& operator=(DoorsOpened&&) = delete;

        constexpr std::string_view name() const noexcept { return "Doors Opened"; }

        void print(std::ostream& os) const noexcept override {
            os << name();
        }

        [[nodiscard]] static const DoorsOpened& instance() noexcept {
            static const DoorsOpened instance;
            return instance;
        }
    };

} // namespace elevator::detail

#endif // ELEVATOR_DETAIL_DOORS_OPENED_H
