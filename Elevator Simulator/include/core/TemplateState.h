// include/core/TemplateState.h
#ifndef CORE_TEMPLATE_STATE_H
#define CORE_TEMPLATE_STATE_H
#include <string_view>
#include <compare>
#include <iostream>

namespace core {

    template <typename Derived, typename DomainBase>
    struct TemplateState : virtual DomainBase {
        TemplateState() = default;

        template<typename... Args>
        TemplateState(Args&&... args) : DomainBase(std::forward<Args>(args)...) {}

        bool equals(const TemplateState& other) const {
            if (typeid(*this) != typeid(other)) return false;
            return this == &other;
        }

        std::strong_ordering compare(const TemplateState& other) const {
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

        void print(std::ostream& os) const {
            static_cast<const Derived*>(this)->print(os);
        }
    };

} // namespace core

#endif // CORE_TEMPLATE_STATE_H