// include/elevator/detail/OperationIdle.h
#ifndef ELEVATOR_DETAIL_OPERATION_IDLE_H
#define ELEVATOR_DETAIL_OPERATION_IDLE_H
#include "TemplateState.h"
namespace elevator::detail {
    struct OperationIdle : TemplateState<OperationIdle, OperationState> {
    private:
        constexpr OperationIdle() = default;

    public:
        OperationIdle(const OperationIdle&) = delete;
        OperationIdle& operator=(const OperationIdle&) = delete;
        OperationIdle(OperationIdle&&) = delete;
        OperationIdle& operator=(OperationIdle&&) = delete;

        constexpr std::string_view name() const { return "Idle"; }

        void print(std::ostream& os) const {
            os << name();
        }

        static const OperationIdle& instance() {
            static const OperationIdle instance{};
            return instance;
        }
    };
}

#endif // ELEVATOR_DETAIL_OPERATION_IDLE_H