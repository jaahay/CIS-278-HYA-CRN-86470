// elevator/detail/Stopped.h
#ifndef ELEVATOR_DETAIL_STOPPED_H
#define ELEVATOR_DETAIL_STOPPED_H

#include "Heading.h"

namespace elevator::detail {

    struct Stopped : core::TemplateState<Stopped, Heading> {
    private:
        Stopped() = default;

    public:
        Stopped(const Stopped&) = delete;
        Stopped& operator=(const Stopped&) = delete;
        Stopped(Stopped&&) = delete;
        Stopped& operator=(Stopped&&) = delete;

        bool IsStopped() const override { return true; }
        bool IsGoingUp() const override { return false; }
        bool IsGoingDown() const override { return false; }

        bool PassedOrigin(const Elevator&, const Passenger&) const override {
            return false;
        }

        bool PassedDestination(const Elevator&, const Passenger&) const override {
            return false;
        }

        constexpr std::string_view name() const noexcept { return "Stopped"; }

        void print(std::ostream& os) const noexcept override {
            os << name();
        }

        [[nodiscard]] static const Stopped& instance() noexcept {
            static const Stopped instance;
            return instance;
        }
    };

} // namespace elevator::detail

#endif // ELEVATOR_DETAIL_STOPPED_H
