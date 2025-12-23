// elevator/detail/DoorsClosed.h
#ifndef ELEVATOR_DETAIL_DOORS_CLOSED_H
#define ELEVATOR_DETAIL_DOORS_CLOSED_H

#include "elevator/detail/DomainState.h"

namespace elevator::detail {

    struct DoorsClosed : core::TemplateState<DoorsClosed, DoorState> {
    private:
        DoorsClosed() = default;

    public:
        DoorsClosed(const DoorsClosed&) = delete;
        DoorsClosed& operator=(const DoorsClosed&) = delete;
        DoorsClosed(DoorsClosed&&) = delete;
        DoorsClosed& operator=(DoorsClosed&&) = delete;

        constexpr bool Opened() const { return false; }
        constexpr bool Closed() const { return true;  }

        constexpr std::string_view name() const noexcept { return "Doors Closed"; }

        void print(std::ostream& os) const noexcept override {
            os << name();
        }

        [[nodiscard]] static const DoorsClosed& instance() noexcept {
            static const DoorsClosed instance;
            return instance;
        }
    };

} // namespace elevator::detail

#endif // ELEVATOR_DETAIL_DOORS_CLOSED_H
