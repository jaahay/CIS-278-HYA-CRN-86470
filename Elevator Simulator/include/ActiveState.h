#ifndef ACTIVE_STATE_H
#define ACTIVE_STATE_H
#include <iostream>
#include <compare>
#include <typeinfo>
#include <string_view>
#include <type_traits>
// CRTP base class with three-way and equality operators
template <typename Derived>
struct ActiveState {
    // Three-way comparison operator
    constexpr auto operator<=>(const Derived& other) const {
        return name() <=> other.name();
    }

    // Equality operator
    constexpr bool operator==(const Derived& other) const {
        return (*this <=> other) == 0;
    }

    // Polymorphic compare with base ref (requires static_cast)
    constexpr bool equals(const ActiveState& other) const {
        if constexpr (std::is_same_v<Derived, std::remove_cvref_t<decltype(other)>>) {
            return *static_cast<const Derived*>(this) == *static_cast<const Derived*>(&other);
        }
        return false;
    }

    // Helper to cast base ref to derived ref (requires all ActiveState objects to be CRTP)
    constexpr const Derived& asDerived() const {
        return static_cast<const Derived&>(*this);
    }

    // Provide interface methods
    constexpr std::string_view name() const {
        return static_cast<const Derived*>(this)->name();
    }

    constexpr std::ostream& operator<<(std::ostream& os) const {
        return os << name();
    }
};

template <typename Derived>
std::ostream& operator<<(std::ostream& os, const ActiveState<Derived>& state) {
    return os << state;
}

// Derived state: Idle
struct Idle : ActiveState<Idle> {
private:
    constexpr Idle() {}

public:
    Idle(const Idle&) = delete;
    Idle& operator=(const Idle&) = delete;
    Idle(Idle&&) = delete;
    Idle& operator=(Idle&&) = delete;
    constexpr std::string_view name() const { return "Idle"; }

    // Compare Idle instances (no data members, always equal)
    constexpr std::strong_ordering compare(const Idle&) const {
        return std::strong_ordering::equal;
    }
    static const Idle IDLE;
};
constexpr Idle Idle::IDLE{};

// Derived state: Active
struct Active : ActiveState<Active> {
private:
    constexpr Active() {}

public:
    Active(const Active&) = delete;
    Active& operator=(const Active&) = delete;
    Active(Active&&) = delete;
    Active& operator=(Active&&) = delete;
    constexpr std::string_view name() const { return "Active"; }

    // Compare Active instances (no data members, always equal)
    constexpr std::strong_ordering compare(const Active&) const {
        return std::strong_ordering::equal;
    }
    static const Active ACTIVE;
};
constexpr Active Active::ACTIVE{};

#endif // ACTIVE_STATE_H