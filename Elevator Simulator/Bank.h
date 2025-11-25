#ifndef BANK_H
#define BANK_H

#include <future>

#include "Elevator.h"
#include "Passenger.h"

class IBank {
    public:
    virtual IElevator &ReceivePassenger(const IPassenger &) = 0;
    // virtual std::future<IElevator *> ReceivePassenger(const IPassenger &) = 0;
    virtual const std::ostream& print(std::ostream&) const = 0;
};

const std::ostream& operator<<(std::ostream& os, const IBank& bank) { return bank.print(os); }

#endif // BANK_H
