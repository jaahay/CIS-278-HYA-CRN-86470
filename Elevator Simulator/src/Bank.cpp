/* Bank.cpp
 * Implementation of the Bank class for Elevator Simulator
 */
#include "Bank.h"
const int Bank::ClosestIdx(const Bank& bank, const Passenger& passenger) const {
    int idx = 0;
    auto leastDivergence = bank.elevators.at(idx)->Divergence(passenger);
    for (int i = 0; i < bank.elevators.size(); ++i) {
        auto divergence = bank.elevators.at(i)->Divergence(passenger);
        // std::cout << "Div: " << divergence;
        if (divergence < leastDivergence) {
            idx = i;
            leastDivergence = divergence;
        }
    }
    return idx;
};

Elevator& Bank::ReceivePassenger(const Passenger& passenger) const {
    auto closestIt = ClosestIdx(*this, passenger);
    auto closest = elevators.at(closestIt);
    std::cout << "Closest elevator found as: " << std::endl;
    std::cout << "\t" << closest << std::endl;
    auto q = closest->ReceivePassenger(passenger);
    return *closest;
};