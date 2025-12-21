// include/elevator/OperationState.h
#ifndef OPERATION_STATE_H
#define OPERATION_STATE_H
#include "OperationActive.h"
#include "BaseState.h"
#include "OperationIdle.h"

struct OperationState : BaseState {

    // Three-way comparison operator
    constexpr std::strong_ordering operator<=>(const Derived& other) const {
        if (this == &other) return std::strong_ordering::equal;
        return this < &other ? std::strong_ordering::less : std::strong_ordering::greater;
    }

    // Equality operator
    constexpr bool operator==(const Derived& other) const {
        return (*this <=> other) == 0;
    }

    // Polymorphic equals using identity
    bool equals(const BaseState& other) const override {
        if (typeid(*this) != typeid(other)) return false;
        return this == &other;  // identity comparison
    }

    // Polymorphic compare using identity
    std::strong_ordering compare(const BaseState& other) const override {
        if (typeid(*this) != typeid(other)) {
            return std::string_view(typeid(*this).name()) <=> std::string_view(typeid(other).name());
        }
        // Same type: compare addresses for ordering
        if (this == &other) return std::strong_ordering::equal;
        return this < &other ? std::strong_ordering::less : std::strong_ordering::greater;
    }

    // Helper to cast base ref to derived ref (requires all BaseState objects to be CRTP)
    constexpr const Derived& asDerived() const {
        return static_cast<const Derived&>(*this);
    }

    // Provide interface methods
    constexpr std::string_view name() const {
        return static_cast<const Derived*>(this)->name();
    }

    void print(std::ostream& os) const override {
        static_cast<const Derived*>(this)->print(os);
    }
};

static inline const IDLE = Idle::instance();
static inline const ACTIVE = Active::instance();

#endif // !OPERATION_STATE_H