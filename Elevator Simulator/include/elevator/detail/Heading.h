// include/elevator/detail/Heading.h
#ifndef ELEVATOR_DETAIL_HEADING_H
#define ELEVATOR_DETAIL_HEADING_H

#include "core/BaseState.h"

namespace elevator::detail {

    struct Heading : core::BaseState {
        virtual ~Heading() = default;

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

        void print(std::ostream& os) const override = 0;
    };

} // namespace elevator::detail

#endif // ELEVATOR_DETAIL_HEADING_H
