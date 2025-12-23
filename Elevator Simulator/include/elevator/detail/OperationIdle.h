// elevator/detail/OperationIdle.h
#ifndef ELEVATOR_DETAIL_OPERATION_IDLE_H
#define ELEVATOR_DETAIL_OPERATION_IDLE_H

#include "elevator/detail/DomainState.h"

namespace elevator::detail {

    struct OperationIdle : core::TemplateState<OperationIdle, OperationState> {
    private:
        OperationIdle() = default;

    public:
        OperationIdle(const OperationIdle&) = delete;
        OperationIdle& operator=(const OperationIdle&) = delete;
        OperationIdle(OperationIdle&&) = delete;
        OperationIdle& operator=(OperationIdle&&) = delete;

        constexpr bool IsActive() const override { return false;  }

        constexpr std::string_view name() const noexcept { return "Idle"; }

        void print(std::ostream& os) const noexcept override {
            os << name();
        }

        [[nodiscard]] static const OperationIdle& instance() noexcept {
            static const OperationIdle instance;
            return instance;
        }
    };

} // namespace elevator::detail

#endif // ELEVATOR_DETAIL_OPERATION_IDLE_H
