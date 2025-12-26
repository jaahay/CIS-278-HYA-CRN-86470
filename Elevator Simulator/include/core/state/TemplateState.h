// core/state/TemplateState.h
#ifndef CORE_STATE_TEMPLATE_STATE_H
#define CORE_STATE_TEMPLATE_STATE_H

#include <string_view>
#include <compare>
#include <iostream>
#include <typeinfo>

#include "core/state/BaseState.h"

namespace core::state {

    template <typename Derived, typename DomainBase = BaseState>
    struct TemplateState : virtual DomainBase {
        TemplateState() = default;

        template<typename... Args>
        TemplateState(Args&&... args) : DomainBase(std::forward<Args>(args)...) {}

        bool equals(const BaseState& other) const override {
            if (typeid(*this) != typeid(other)) return false;
            auto p = dynamic_cast<const Derived*>(&other);
            return p && this == p;
        }

        std::strong_ordering compare(const BaseState& other) const override {
            if (typeid(*this) != typeid(other)) {
                return std::string_view(typeid(*this).name()) <=> std::string_view(typeid(other).name());
            }
            auto p = dynamic_cast<const Derived*>(&other);
            if (!p) return std::strong_ordering::less;
            if (this == p) return std::strong_ordering::equal;
            return this < p ? std::strong_ordering::less : std::strong_ordering::greater;
        }

        constexpr std::strong_ordering operator<=>(const Derived& other) const {
            return this == &other ? std::strong_ordering::equal :
                this < &other ? std::strong_ordering::less : std::strong_ordering::greater;
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

} // namespace core::state

#endif // CORE_STATE_TEMPLATE_STATE_H
