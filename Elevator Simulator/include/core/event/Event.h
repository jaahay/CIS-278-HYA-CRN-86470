// core/event/Event.h
#ifndef CORE_EVENT_EVENT_H
#define CORE_EVENT_EVENT_H

namespace core::event {

    struct Event {
        virtual ~Event() = default;
    };

    enum class CallbackPhase {
        Before,
        Main,
        After
    };

} // namespace core::event

#endif // CORE_EVENT_EVENT_H
