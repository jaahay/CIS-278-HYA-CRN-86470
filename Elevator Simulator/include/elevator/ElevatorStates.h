#ifndef ELEVATOR_STATES_H
#define ELEVATOR_STATES_H

#include "detail/DomainStates.h"
#include "detail/OperationActive.h"
#include "detail/OperationIdle.h"
#include "detail/TemplateState.h"

namespace elevator {

	// Expose domain bases and CRTP template to users

	using detail::DirectionState;
	using detail::OperationState;

	template <typename Derived, typename DomainBase>
	using TemplateState = detail::TemplateState<Derived, DomainBase>;

	inline constexpr OperationState& ACTIVE = detail::OperationActive::instance();
	inline constexpr OperationState& IDLE = detail::OperationIdle::instance();


} // namespace elevator

#endif // ELEVATOR_STATES_H