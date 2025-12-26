// core/event/EventCallback.h
#ifndef CORE_EVENT_EVENT_CALLBACK_H
#define CORE_EVENT_EVENT_CALLBACK_H

#include "Event.h"
#include <functional>

namespace core::event {

    struct IEventCallback {
        virtual bool Invoke(const Event&) const = 0;
        virtual CallbackPhase Phase() const = 0;
        virtual const core::state::BaseState* Priority() const = 0;
        virtual ~IEventCallback() = default;
    };

    template <typename EventT>
    class EventCallback : public IEventCallback {
    public:
        using CallbackFunc = std::function<void(const EventT&)>;

        EventCallback(CallbackFunc cb,
            CallbackPhase phase,
            const core::state::BaseState& priority)
            : callback_(std::move(cb)), phase_(phase), priority_(&priority) {
        }

        bool Invoke(const Event& baseEvent) const override {
            if (auto derived = dynamic_cast<const EventT*>(&baseEvent)) {
                callback_(*derived);
                return true;
            }
            return false;
        }

        CallbackPhase Phase() const override { return phase_; }

        const core::state::BaseState* Priority() const override { return priority_; }

    private:
        CallbackFunc callback_;
        CallbackPhase phase_;
        const core::state::BaseState* priority_;
    };

} // namespace core::event

#endif // CORE_EVENT_EVENT_CALLBACK_H
