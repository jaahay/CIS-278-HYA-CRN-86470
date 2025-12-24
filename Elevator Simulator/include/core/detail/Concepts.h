// core/detail/Concepts.h
#ifndef CORE_DETAIL_CONCEPTS_H
#define CORE_DETAIL_CONCEPTS_H

#include <type_traits>
#include <concepts>
#include "core/detail/BaseState.h"

namespace core::detail::concepts {

	// Concept: type must derive from BaseState
	template <typename T>
	concept DerivedFromBaseState = std::is_base_of_v<BaseState, T>;

	// Minimal concept for event-like types (copy constructible)
	template <typename EventT>
	concept EventLike = std::copy_constructible<EventT>;

} // namespace core::detail

#endif // CORE_DETAIL_CONCEPTS_H
