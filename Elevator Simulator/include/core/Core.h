// core/Core.h
#ifndef CORE_H
#define CORE_H

// Include the actual detailed headers
#include "detail/BaseState.h"
#include "detail/TemplateState.h"

// Forward types into core namespace
namespace core {

    using BaseState = detail::BaseState;
    template <typename Derived, typename DomainBase>
    using TemplateState = detail::TemplateState<Derived, DomainBase>;

    using detail::operator==;
    using detail::operator!=;
    using detail::operator<=>;

} // namespace core

#endif // CORE_H
