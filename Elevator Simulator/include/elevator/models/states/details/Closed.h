// elevator/models/states/details/Closed.h
#ifndef ELEVATORS_STATES_CLOSED_H
#define ELEVATORS_STATES_CLOSED_H

#include "elevator/models/states/Types.h"

namespace elevator::model::states::details {

    struct Closed : core::TemplateState<Closed, DoorState> {
    private:
        Closed() = default;

    public:
        Closed(const Closed&) = delete;
        Closed& operator=(const Closed&) = delete;
        Closed(Closed&&) = delete;
        Closed& operator=(Closed&&) = delete;

        constexpr bool Opened() const { return false; }
        constexpr bool Closed() const { return true;  }

        constexpr std::string_view name() const noexcept { return "Closed"; }

        void print(std::ostream& os) const noexcept override {
            os << name();
        }

        [[nodiscard]] static const Closed& instance() noexcept {
            static const Closed instance;
            return instance;
        }
    };

} // namespace elevator::model::states::details

#endif // ELEVATORS_STATES_CLOSED_H
