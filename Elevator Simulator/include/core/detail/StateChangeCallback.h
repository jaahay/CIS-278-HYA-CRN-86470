// core/detail/StateChangeCallback.h
#ifndef CORE_DETAIL_STATE_CHANGE_CALLBACK_H
#define CORE_DETAIL_STATE_CHANGE_CALLBACK_H

#include <functional>
#include <concepts>
#include <utility>
#include <stdexcept>

#include "Concepts.h"

namespace core::detail {

    template <EventLike EventT>
    class StateChangeCallback {
    public:
        using CallbackType = std::function<void(const EventT&)>;

        StateChangeCallback() : callback_([](const EventT&) {}) {}

        explicit StateChangeCallback(CallbackType cb) : callback_(std::move(cb)) {}

        void operator()(const EventT& event) const {
            callback_(event);
        }

        // Compose two callbacks into one that calls both in order
        StateChangeCallback Compose(const StateChangeCallback& other) const {
            if (!callback_) return other;
            if (!other.callback_) return *this;
            return StateChangeCallback([first = callback_, second = other.callback_](const EventT& e) {
                first(e);
                second(e);
                });
        }

        // operator+= for easier chaining
        StateChangeCallback& operator+=(const StateChangeCallback& other) {
            *this = this->Compose(other);
            return *this;
        }

        explicit operator bool() const {
            return static_cast<bool>(callback_);
        }

    private:
        CallbackType callback_;
    };

} // namespace core::detail

#endif // CORE_DETAIL_STATE_CHANGE_CALLBACK_H