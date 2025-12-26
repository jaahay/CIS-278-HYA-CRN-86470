// core/event/CallbackPhaseState.h
#ifndef CORE_EVENT_CALLBACK_PHASE_STATE_H
#define CORE_EVENT_CALLBACK_PHASE_STATE_H

#include "core/state/TemplateState.h"

namespace core::event {

    struct CallbackPhaseState : core::state::BaseState {
        virtual ~CallbackPhaseState() = default;
    };

    struct BeforePhase : core::state::TemplateState<BeforePhase, CallbackPhaseState> {
    private:
        BeforePhase() = default;
    public:
        static const BeforePhase& instance() {
            static BeforePhase inst;
            return inst;
        }
        constexpr std::string_view name() const noexcept { return "Before"; }
        void print(std::ostream& os) const noexcept override { os << name(); }
    };

    struct MainPhase : core::state::TemplateState<MainPhase, CallbackPhaseState> {
    private:
        MainPhase() = default;
    public:
        static const MainPhase& instance() {
            static MainPhase inst;
            return inst;
        }
        constexpr std::string_view name() const noexcept { return "Main"; }
        void print(std::ostream& os) const noexcept override { os << name(); }
    };

    struct AfterPhase : core::state::TemplateState<AfterPhase, CallbackPhaseState> {
    private:
        AfterPhase() = default;
    public:
        static const AfterPhase& instance() {
            static AfterPhase inst;
            return inst;
        }
        constexpr std::string_view name() const noexcept { return "After"; }
        void print(std::ostream& os) const noexcept override { os << name(); }
    };

} // namespace core::event

#endif // CORE_EVENT_CALLBACK_PHASE_STATE_H
