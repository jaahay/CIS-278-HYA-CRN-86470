/* Bank.cpp
 * Implementation of the Bank class for Elevator Simulator
 */
#include "elevator/Bank.h"

template<class Elevator, class Passenger>
const int Bank<Elevator, Passenger>::ClosestIdx(const Passenger& passenger) const {
    int idx = 0;
    auto leastDivergence = elevators.at(idx)->Divergence(passenger);
    for (int i = 0; i < elevators.size(); ++i) {
        auto divergence = elevators.at(i)->Divergence(passenger);
        // std::cout << "Div: " << divergence;
        if (divergence < leastDivergence) {
            idx = i;
            leastDivergence = divergence;
        }
    }
    return idx;
};
template<class Elevator, class Passenger>
Elevator& Bank<Elevator, Passenger>::ReceivePassenger(const Passenger& passenger) const {
    auto closestIt = ClosestIdx(*this, passenger);
    auto closest = elevators.at(closestIt);
    std::cout << "Closest elevator found as: " << std::endl;
    std::cout << "\t" << closest << std::endl;
    auto q = closest->ReceivePassenger(passenger);
    return *closest;
};