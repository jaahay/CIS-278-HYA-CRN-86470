// core/event/EventHierarchy.h
#ifndef CORE_EVENT_EVENT_HIERARCHY_H
#define CORE_EVENT_EVENT_HIERARCHY_H

#include <typeindex>
#include <vector>

namespace core::event {

    // Default: event hierarchy is just the event itself
    template <typename EventT>
    struct EventHierarchy {
        static const std::vector<std::type_index>& Get() {
            static const std::vector<std::type_index> hierarchy = { std::type_index(typeid(EventT)) };
            return hierarchy;
        }
    };

} // namespace core::event

#endif // CORE_EVENT_EVENT_HIERARCHY_H
