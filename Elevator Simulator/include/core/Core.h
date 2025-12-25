// core/Core.h
#ifndef CORE_H
#define CORE_H

//#include "core/concepts/Concepts.h"
#include "core/event/ChangeEventDispatcher.h"
#include "core/event/StateChangeCallback.h"
#include "core/event/StateChangeEvent.h"
#include "core/state/BaseState.h"
#include "core/state/TemplateState.h"

namespace core {

    using BaseState = state::BaseState;

    template <typename Derived, typename DomainBase = BaseState>
    using TemplateState = state::TemplateState<Derived, DomainBase>;

    using state::operator==;
    using state::operator!=;
    using state::operator<=>;

    using concepts::DerivedFromBaseState;
    using concepts::EventLike;

    template <typename ObjectType, typename StateType>
    using StateChangeEvent = event::StateChangeEvent<ObjectType, StateType>;

    template <EventLike EventT>
    using StateChangeCallback = event::StateChangeCallback<EventT>;

    template <typename ObjectType, typename StateType>
    using ChangeEventDispatcher = event::ChangeEventDispatcher<ObjectType, StateType>;

} // namespace core

#endif // CORE_H
