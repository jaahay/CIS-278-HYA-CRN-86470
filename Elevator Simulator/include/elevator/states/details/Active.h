// elevator/states/details/Active.h
#ifndef ELEVATOR_STATES_DETAILS_ACTIVE_H
#define ELEVATOR_STATES_DETAILS_ACTIVE_H

#include "elevator/states/Types.h"

namespace elevator::states::details {

    struct Active : core::TemplateState<Active, OperationState> {
    private:
        Active() = default;

    public:
        Active(const Active&) = delete;
        Active& operator=(const Active&) = delete;
        Active(Active&&) = delete;
        Active& operator=(Active&&) = delete;

        constexpr bool IsActive() const override { return true; }

        constexpr std::string_view name() const noexcept { return "Active"; }

        void print(std::ostream& os) const noexcept override {
            os << name();
        }

        [[nodiscard]] static const Active& instance() noexcept {
            static const Active instance;
            return instance;
        }
    };

} // namespace elevator::states::details

#endif // ELEVATOR_STATES_DETAILS_ACTIVE_H
