// core/detail/CallbackUtils.h
#ifndef CORE_DETAIL_CALLBACK_UTILS_H
#define CORE_DETAIL_CALLBACK_UTILS_H

#include "core/detail/StateChangeCallback.h"
#include "core/detail/Concepts.h"

namespace core::detail:utils {

    template <EventLike EventT>
    inline StateChangeCallback<EventT> NoOpCallback() {
        return StateChangeCallback<EventT>([](const EventT&) {});
    }

} // namespace core::detail

#endif // CORE_DETAIL_CALLBACK_UTILS_H