// core/Core.h
#ifndef CORE_H
#define CORE_H

#include "detail/BaseState.h"
#include "detail/Concepts.h"
#include "detail/StateChangeCallback.h"
#include "detail/StateChangeEvent.h"
#include "detail/TemplateState.h"
#include "detail/StateEventDispatcher.h"

namespace core {

    using BaseState = detail::BaseState;

    template <typename Derived, typename DomainBase = BaseState>
    using TemplateState = detail::TemplateState<Derived, DomainBase>;

    using detail::operator==;
    using detail::operator!=;
    using detail::operator<=>;

    using detail::DerivedFromBaseState;
    using detail::EventLike;

    template <typename Category>
    using StateChangeEvent = detail::StateChangeEvent<Category>;

    template <typename EventT>
    using StateChangeCallback = detail::StateChangeCallback<EventT>;

    template <typename Category>
    using StateEventDispatcher = detail::StateEventDispatcher<Category>;

} // namespace core

#endif // CORE_H
