// core/Core.h
#ifndef CORE_H
#define CORE_H

#include "detail/BaseState.h"
#include "detail/Concepts.h"
#include "detail/StateChangeCallback.h"
#include "detail/StateChangeEvent.h"
#include "detail/StateEventDispatcher.h"
#include "detail/TemplateState.h"

namespace core {

    // Base polymorphic state type
    using BaseState = detail::BaseState;

    // CRTP template for states
    template <typename Derived, typename DomainBase = BaseState>
    using TemplateState = detail::TemplateState<Derived, DomainBase>;

    // Comparison operators from detail namespace
    using detail::operator==;
    using detail::operator!=;
    using detail::operator<=>;

    // Concepts for type constraints
    using detail::DerivedFromBaseState;
    using detail::StateDerivedFromCategory;
    using detail::EventLike;

    // Template aliases for event system
    template <typename Category, typename State>
    using StateChangeEvent = detail::StateChangeEvent<Category, State>;

    template <typename EventT>
    using StateChangeCallback = detail::StateChangeCallback<EventT>;

    template <typename Category, typename State>
    using StateEventDispatcher = detail::StateEventDispatcher<Category, State>;

} // namespace core

#endif // CORE_H
