// include/elevator/detail/OperationActive.h
#ifndef ELEVATOR_DETAIL_OPERATION_ACTIVE_H
#define ELEVATOR_DETAIL_OPERATION_ACTIVE_H
#include "core/TemplateState.h"
#include "OperationState.h"
namespace elevator::detail {

    struct OperationActive : core::TemplateState<OperationActive, OperationState> {

    private:

        OperationActive() = default;

    public:

        //static const OperationActive instance;

        // Delete copy/move to enforce singleton
        OperationActive(const OperationActive&) = delete;
        OperationActive& operator=(const OperationActive&) = delete;
        OperationActive(OperationActive&&) = delete;
        OperationActive& operator=(OperationActive&&) = delete;

        constexpr std::string_view name() const { return "Active"; }

        void print(std::ostream& os) const {
            os << name();
        }

        static const OperationActive& instance() {
            static const OperationActive instance;
            return instance;
        }
    };

} // namespace elevator::detail

#endif // ELEVATOR_DETAIL_OPERATION_ACTIVE_H