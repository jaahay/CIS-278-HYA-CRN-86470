// core/concepts/Concepts.h
#ifndef CORE_CONCEPTS_CONCEPTS_H
#define CORE_CONCEPTS_CONCEPTS_H

#include <type_traits>
#include <concepts>
#include "core/state/BaseState.h"

namespace core::concepts {

	// Concept: type must derive from BaseState
	template <typename T>
	concept DerivedFromBaseState = std::is_base_of_v<BaseState, T>;

	// Minimal concept for event-like types (copy constructible)
	template <typename EventT>
	concept EventLike = std::copy_constructible<EventT>;

} // namespace core::concepts

#endif // CORE_CONCEPTS_CONCEPTS_H
