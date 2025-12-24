// core/Core.h
#ifndef CORE_H
#define CORE_H

#include "core/concepts/Concepts.h"
#include "core/event/StateChangeCallback.h"
#include "core/event/StateChangeDispatcher.h"
#include "core/event/StateChangeEvent.h"
#include "core/state/BaseState.h"
#include "core/state/TemplateState.h"

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
