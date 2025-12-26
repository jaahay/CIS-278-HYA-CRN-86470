// core/event/DefaultPriorityState.h
#ifndef CORE_EVENT_DEFAULT_PRIORITY_STATE_H
#define CORE_EVENT_DEFAULT_PRIORITY_STATE_H

#include "core/state/TemplateState.h"
#include "PriorityState.h"

namespace core::event {

    // Default priority base (lowest priority)
    struct DefaultPriority : core::state::TemplateState<DefaultPriority, PriorityState> {
    private:
        DefaultPriority() = default;
    public:
        static const DefaultPriority& instance() {
            static DefaultPriority inst;
            return inst;
        }
        constexpr std::string_view name() const noexcept { return "DefaultPriority"; }
        void print(std::ostream& os) const noexcept override { os << name(); }
    };

    // Optional higher priority example
    struct HighPriority : core::state::TemplateState<HighPriority, PriorityState> {
    private:
        HighPriority() = default;
    public:
        static const HighPriority& instance() {
            static HighPriority inst;
            return inst;
        }
        constexpr std::string_view name() const noexcept { return "HighPriority"; }
        void print(std::ostream& os) const noexcept override { os << name(); }
    };

} // namespace core::event

#endif // CORE_EVENT_DEFAULT_PRIORITY_STATE_H
