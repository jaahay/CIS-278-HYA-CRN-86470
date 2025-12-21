// include/elevator/detail/OperationActive.h
#ifndef ELEVATOR_DETAIL_OPERATION_ACTIVE_H
#define ELEVATOR_DETAIL_OPERATION_ACTIVE_H
#include "TemplateState.h"
namespace elevator::detail {
    struct OperationActive : TemplateState<OperationActive, OperationState> {
    public:
        constexpr OperationActive() = default;
        static inline const OperationActive instance;

        // Delete copy/move to enforce singleton
        OperationActive(const OperationActive&) = delete;
        OperationActive& operator=(const OperationActive&) = delete;
        OperationActive(OperationActive&&) = delete;
        OperationActive& operator=(OperationActive&&) = delete;

        constexpr std::string_view name() const { return "Active"; }

        void print(std::ostream& os) const {
            os << name();
        }

    };
    //inline constexpr const OperationActive OperationActive::instance{};
} // namespace elevator::detail

#endif // ELEVATOR_DETAIL_OPERATION_ACTIVE_H