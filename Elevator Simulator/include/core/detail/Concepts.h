// core/detail/Concepts.h
#ifndef CORE_DETAIL_CONCEPTS_H
#define CORE_DETAIL_CONCEPTS_H

#include <type_traits>
#include <concepts>
#include "BaseState.h"

namespace core::detail {

	// Concept: type must derive from BaseState
	template <typename T>
	concept DerivedFromBaseState = std::is_base_of_v<BaseState, T>;

	// Concept: State must derive from Category
	template <typename Category, typename State>
	concept StateDerivedFromCategory = std::is_base_of_v<Category, State>;

	// Minimal concept for event-like types (copy constructible)
	template <typename EventT>
	concept EventLike = std::copy_constructible<EventT>;

} // namespace core::detail

#endif // CORE_DETAIL_CONCEPTS_H
