// include/elevator/detail/TemplateState.h
#ifndef ELEVATOR_DETAIL_TEMPLATE_STATE_H
#define ELEVATOR_DETAIL_TEMPLATE_STATE_H

#include "DomainStates.h"
#include <type_traits>
#include <string_view>
#include <typeinfo>

namespace elevator::detail {

    template <typename Derived, typename DomainBase>
    struct TemplateState : DomainBase {
        constexpr TemplateState() = default;

        bool equals(const BaseState& other) const override {
            if (typeid(*this) != typeid(other)) return false;
            return this == &other;
        }

        std::strong_ordering compare(const BaseState& other) const override {
            if (typeid(*this) != typeid(other)) {
                return std::string_view(typeid(*this).name()) <=> std::string_view(typeid(other).name());
            }
            if (this == &other) return std::strong_ordering::equal;
            return this < &other ? std::strong_ordering::less : std::strong_ordering::greater;
        }

        constexpr std::strong_ordering operator<=>(const Derived& other) const {
            if (this == &other) return std::strong_ordering::equal;
            return this < &other ? std::strong_ordering::less : std::strong_ordering::greater;
        }

        constexpr bool operator==(const Derived& other) const {
            return this == &other;
        }

        constexpr std::string_view name() const {
            return static_cast<const Derived*>(this)->name();
        }

        void print(std::ostream& os) const override {
            static_cast<const Derived*>(this)->print(os);
        }
    };

} // namespace elevator::detail

#endif // ELEVATOR_DETAIL_TEMPLATE_STATE_H