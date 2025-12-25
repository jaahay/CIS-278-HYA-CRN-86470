// core/concepts/Concepts.h
#ifndef CORE_CONCEPTS_CONCEPTS_H
#define CORE_CONCEPTS_CONCEPTS_H

#include <type_traits>
#include <concepts>
#include "core/state/BaseState.h"

namespace core::concepts {
	
	// Checks if a type is abstract
	template <typename T>
	concept Abstract = std::is_abstract_v<T>;

	// Checks if a type is concrete (not abstract)
	template <typename T>
	concept Concrete = !std::is_abstract_v<T>;

	template <typename Derived, typename Base>
	concept DerivedFrom = std::is_base_of_v<Base, Derived>;

	// Concept: type must derive from BaseState
	template <typename T>
	concept DerivedFromBaseState = std::is_base_of_v<core::state::BaseState, T>;

	template <typename StateType, typename ObjectType>
	concept ValidStateType =
		Concrete<StateType> &&
		DerivedFrom<StateType, ObjectType>&&
		DerivedFromBaseState<StateType>;

	// Minimal concept for event-like types (copy constructible)
	template <typename EventT>
	concept EventLike = std::copy_constructible<EventT>;

	template <typename F, typename Arg>
	concept CallableWith = requires(F f, Arg arg) {
		{ f(arg) } -> std::same_as<void>;
	};

} // namespace core::concepts

#endif // CORE_CONCEPTS_CONCEPTS_H
