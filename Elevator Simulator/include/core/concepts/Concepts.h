// core/concepts/Concepts.h
#ifndef CORE_CONCEPTS_CONCEPTS_H
#define CORE_CONCEPTS_CONCEPTS_H

#include <type_traits>
#include <concepts>
#include "core/state/BaseState.h"
#include "core/event/Event.h"

namespace core::concepts {

    template <typename T>
    concept DerivedFromBaseState = std::is_base_of_v<core::state::BaseState, T>;

    template <typename T>
    concept SingletonState = requires {
        { T::instance() } -> std::same_as<const T&>;
    };

    template <typename T>
    concept ConcreteState = DerivedFromBaseState<T> && !std::is_abstract_v<T>;

    template <typename T>
    concept EventType = std::is_base_of_v<core::event::Event, T>;

    template <typename F, typename EventT>
    concept CallableWithEvent = requires(F f, EventT e) {
        { f(e) } -> std::same_as<void>;
    };

} // namespace core::concepts

#endif // CORE_CONCEPTS_CONCEPTS_H
