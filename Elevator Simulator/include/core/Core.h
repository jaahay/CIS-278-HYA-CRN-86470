// core/Core.h
#ifndef CORE_H
#define CORE_H

#include "core/detail/BaseState.h"
#include "core/detail/Concepts.h"
#include "core/detail/StateChangeCallback.h"
#include "core/detail/StateChangeEvent.h"
#include "core/detail/TemplateState.h"
#include "core/detail/EventDispatcher.h"

namespace core {

    using BaseState = detail::BaseState;

    template <typename Derived, typename DomainBase = BaseState>
    using TemplateState = detail::TemplateState<Derived, DomainBase>;

    using detail::operator==;
    using detail::operator!=;
    using detail::operator<=>;

    using detail::concepts::DerivedFromBaseState;
    using detail::concepts::EventLike;

    template <typename Category>
    using StateChangeEvent = detail::StateChangeEvent<Category>;

    template <EventLike EventT>
    using StateChangeCallback = detail::StateChangeCallback<EventT>;

    template <typename Category>
    using EventDispatcher = detail::EventDispatcher<Category>;

} // namespace core

#endif // CORE_H
