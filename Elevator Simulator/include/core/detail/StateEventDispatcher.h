// core/detail/StateEventDispatcher.h      
#ifndef CORE_DETAIL_STATE_EVENT_DISPATCHER_H
#define CORE_DETAIL_STATE_EVENT_DISPATCHER_H

#include "StateChangeCallback.h"
#include "StateChangeEvent.h"
#include "Concepts.h"
#include <mutex>
#include <unordered_map>
#include <atomic>
#include <iostream>

namespace core::detail {

    template <typename Category>
        requires DerivedFromBaseState<Category>
    class StateEventDispatcher {
    public:
        using EventType = StateChangeEvent<Category>;
        using CallbackType = StateChangeCallback<EventType>;
        using ObserverId = unsigned int;

        StateEventDispatcher() : nextId_(1) {}

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

        void Notify(const Category& state) {
            StateChangeEvent<Category> event(state);

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
                    std::cerr << "[StateEventDispatcher] Observer ID " << id << " threw: " << e.what() << "\n";
                }
                catch (...) {
                    std::cerr << "[StateEventDispatcher] Observer ID " << id << " threw unknown exception\n";
                }
            }
        }

    private:
        std::mutex mutex_;
        std::unordered_map<ObserverId, CallbackType> observers_;
        std::atomic<ObserverId> nextId_;
    };

} // namespace core::detail

#endif // CORE_DETAIL_STATE_EVENT_DISPATCHER_H
