// core/detail/StateEventDispatcher.h      
// core/detail/EventDispatcher.h

#ifndef CORE_DETAIL_EVENT_DISPATCHER_H
#define CORE_DETAIL_EVENT_DISPATCHER_H

#include "StateChangeCallback.h"
#include <mutex>
#include <unordered_map>
#include <atomic>
#include <iostream>

namespace core::detail {

    template <typename EventT>
    class EventDispatcher {
    public:
        using CallbackType = StateChangeCallback<const EventT&>;
        using ObserverId = unsigned int;

        EventDispatcher() : nextId_(1) {}

        ObserverId AddObserver(CallbackType observer) {
            std::lock_guard lock(mutex_);
            ObserverId id = nextId_++;
            observers_.emplace(id, std::move(observer));
            return id;
        }

        bool RemoveObserver(ObserverId id) {
            std::lock_guard lock(mutex_);
            return observers_.erase(id) > 0;
        }

        void Notify(const EventT& event) {
            std::unordered_map<ObserverId, CallbackType> snapshot;
            {
                std::lock_guard lock(mutex_);
                snapshot = observers_;
            }
            for (const auto& [id, observer] : snapshot) {
                try {
                    observer(event);
                }
                catch (const std::exception& e) {
                    std::cerr << "[EventDispatcher] Observer ID " << id << " threw: " << e.what() << "\n";
                }
                catch (...) {
                    std::cerr << "[EventDispatcher] Observer ID " << id << " threw unknown exception\n";
                }
            }
        }

    private:
        std::mutex mutex_;
        std::unordered_map<ObserverId, CallbackType> observers_;
        std::atomic<ObserverId> nextId_;
    };

} // namespace core::detail

#endif // CORE_DETAIL_EVENT_DISPATCHER_H