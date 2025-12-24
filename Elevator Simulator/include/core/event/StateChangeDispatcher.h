// core/event/ChangeEventDispatcher.h

#ifndef CORE_EVENT_CHANGE_EVENT_DISPATCHER_H
#define CORE_EVENT_CHANGE_EVENT_DISPATCHER_H

#include "core/state/StateChangeCallback.h"
#include <mutex>
#include <unordered_map>
#include <atomic>
#include <iostream>

namespace core::event {

    template <typename ObjectType, typename StateType>
    using StateChangeCallback = core::event::StateChangeCallback<StateChangeEvent<ObjectType, StateType>>;

    template <typename ObjectType, typename StateType>
    class StateChangeDispatcher {
    public:
        using EventT = StateChangeEvent<ObjectType, StateType>;
        using CallbackType = StateChangeCallback<ObjectType, StateType>;
        using ObserverId = unsigned int;

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

        void Notify(const ObjectType& obj, const StateType& state) {
            EventT event(obj, state);
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
                    std::cerr << "[StateChangeDispatcher] Observer ID " << id << " threw: " << e.what() << "\n";
                }
                catch (...) {
                    std::cerr << "[StateChangeDispatcher] Observer ID " << id << " threw unknown exception\n";
                }
            }
        }

    private:
        std::mutex mutex_;
        std::unordered_map<ObserverId, CallbackType> observers_;
        std::atomic<ObserverId> nextId_{ 1 };
    };

} // namespace core::event

#endif // CORE_EVENT_CHANGE_EVENT_DISPATCHER_H