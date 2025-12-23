// elevator/Domain.h
#ifndef ELEVATOR_DOMAIN_H
#define ELEVATOR_DOMAIN_H

#include "elevator/DomainStates.h"
#include "elevator/DomainRegistry.h"
#include "elevator/DomainEvent.h"
#include "elevator/ElevatorEventDispatcher.h"

namespace elevator {

    template <typename Variant, typename Visitor>
    void VisitDomainState(const Variant& variant, Visitor&& visitor) {
        std::visit(std::forward<Visitor>(visitor), variant);
    }

    template <typename Variant>
    void PrintDomainState(const Variant& variant, std::ostream& os) {
        std::visit([&os](const auto& state) {
            state.print(os);
            }, variant);
    }

} // namespace elevator

#endif // ELEVATOR_DOMAIN_H