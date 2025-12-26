// core/event/ScopedCallbackHandler.h
#ifndef CORE_EVENT_SCOPED_CALLBACK_HANDLER_H
#define CORE_EVENT_SCOPED_CALLBACK_HANDLER_H

#include <cstddef>

namespace core::event {

    class EventDispatcher; // Forward declaration

    class ScopedCallbackHandler {
    public:
        ScopedCallbackHandler() = default;

        ScopedCallbackHandler(EventDispatcher& dispatcher, size_t handle)
            : dispatcher_(&dispatcher), handle_(handle) {
        }

        ~ScopedCallbackHandler() {
            if (dispatcher_ && handle_ != 0) {
                dispatcher_->RemoveCallback(handle_);
            }
        }

        ScopedCallbackHandler(const ScopedCallbackHandler&) = delete;
        ScopedCallbackHandler& operator=(const ScopedCallbackHandler&) = delete;

        ScopedCallbackHandler(ScopedCallbackHandler&& other) noexcept
            : dispatcher_(other.dispatcher_), handle_(other.handle_) {
            other.dispatcher_ = nullptr;
            other.handle_ = 0;
        }

        ScopedCallbackHandler& operator=(ScopedCallbackHandler&& other) noexcept {
            if (this != &other) {
                if (dispatcher_ && handle_ != 0) {
                    dispatcher_->RemoveCallback(handle_);
                }
                dispatcher_ = other.dispatcher_;
                handle_ = other.handle_;
                other.dispatcher_ = nullptr;
                other.handle_ = 0;
            }
            return *this;
        }

        explicit operator bool() const { return handle_ != 0; }

        size_t Get() const { return handle_; }

    private:
        EventDispatcher* dispatcher_ = nullptr;
        size_t handle_ = 0;
    };

} // namespace core::event

#endif // CORE_EVENT_SCOPED_CALLBACK_HANDLER_H
