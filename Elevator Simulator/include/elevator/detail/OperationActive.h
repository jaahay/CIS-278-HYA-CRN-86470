// elevator/detail/OperationActive.h
#ifndef ELEVATOR_DETAIL_OPERATION_ACTIVE_H
#define ELEVATOR_DETAIL_OPERATION_ACTIVE_H

#include "OperationState.h"

namespace elevator::detail {

    struct OperationActive : core::TemplateState<OperationActive, OperationState> {
    private:
        OperationActive() = default;

    public:
        OperationActive(const OperationActive&) = delete;
        OperationActive& operator=(const OperationActive&) = delete;
        OperationActive(OperationActive&&) = delete;
        OperationActive& operator=(OperationActive&&) = delete;

        constexpr std::string_view name() const noexcept { return "Active"; }

        void print(std::ostream& os) const noexcept override {
            os << name();
        }

        [[nodiscard]] static const OperationActive& instance() noexcept {
            static const OperationActive instance;
            return instance;
        }
    };

} // namespace elevator::detail

#endif // ELEVATOR_DETAIL_OPERATION_ACTIVE_H
