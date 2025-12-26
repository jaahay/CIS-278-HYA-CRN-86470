// core/event/PriorityState.h
#ifndef CORE_EVENT_PRIORITY_STATE_H
#define CORE_EVENT_PRIORITY_STATE_H

#include "core/state/BaseState.h"
#include "core/meta/TypeList.h"
#include <string_view>

namespace core::event {

    // Base priority state with compile-time relative priority list
    template <typename Derived>
    struct PriorityState : core::state::TemplateState<Derived, core::state::BaseState> {
        // Consumer must define this alias listing types this priority is higher than
        using HigherThanList = core::meta::TypeList<>;

        // Compile-time check if Derived is higher than Other
        template <typename Other>
        static constexpr bool IsHigherThan() {
            return core::meta::Contains<Other, typename Derived::HigherThanList>::value;
        }

        // Polymorphic compare override for runtime sorting
        std::strong_ordering compare(const core::state::BaseState& otherBase) const override {
            // Try dynamic cast to PriorityState base
            const auto* other = dynamic_cast<const PriorityState*>(&otherBase);
            if (!other) {
                // Different base type: fallback to type name ordering
                return std::string_view(typeid(*this).name()) <=> std::string_view(typeid(otherBase).name());
            }

            // Use compile-time IsHigherThan for relative ordering
            if (IsHigherThan<std::remove_pointer_t<decltype(other)>>()) {
                return std::strong_ordering::less; // this < other means this is higher priority
            }
            if (other->template IsHigherThan<Derived>()) {
                return std::strong_ordering::greater;
            }
            // No explicit relation, fallback to type name ordering
            return std::string_view(typeid(*this).name()) <=> std::string_view(typeid(otherBase).name());
        }

        bool equals(const core::state::BaseState& otherBase) const override {
            return typeid(*this) == typeid(otherBase);
        }

        void print(std::ostream& os) const override {
            os << static_cast<const Derived*>(this)->name();
        }
    };

} // namespace core::event

#endif
