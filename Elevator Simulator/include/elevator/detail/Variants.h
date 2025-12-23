// elevator/detail/Variants.h

#ifndef ELEVATOR_DETAIL_VARIANTS_H
#define ELEVATOR_DETAIL_VARIANTS_H

#include "core/detail/MetaUtils.h"
#include "elevator/detail/DoorsClosed.h"
#include "elevator/detail/DoorsClosing.h"
#include "elevator/detail/DoorsOpened.h"
#include "elevator/detail/DoorsOpening.h"

#include "elevator/detail/GoingUp.h"
#include "elevator/detail/GoingDown.h"
#include "elevator/detail/Stopped.h"

#include "elevator/detail/OperationActive.h"
#include "elevator/detail/OperationIdle.h"

namespace elevator {

    // Category variants
    using DoorStateVariant = std::variant<
        const detail::DoorsClosed*,
        const detail::DoorsClosing*,
        const detail::DoorsOpened*,
        const detail::DoorsOpening*
    >;

    using HeadingVariant = std::variant<
        const detail::GoingUp*,
        const detail::GoingDown*,
        const detail::Stopped*
    >;

    using OperationVariant = std::variant<
        const detail::OperationActive*,
        const detail::OperationIdle*
    >;

    //// Compose domain variant from category variants
    //using DomainStateVariant = core::detail::meta::variant_concat_t<
    //    DoorStateVariant,
    //    HeadingVariant,
    //    OperationVariant
    //>;
    using DomainStateVariant = std::variant<
        const detail::DoorsClosed*,
        const detail::DoorsClosing*,
        const detail::DoorsOpened*,
        const detail::DoorsOpening*,
        const detail::GoingUp*,
        const detail::GoingDown*,
        const detail::Stopped*,
        const detail::OperationActive*,
        const detail::OperationIdle*
    >;
}

#endif // ELEVATOR_DETAIL_VARIANTS_H