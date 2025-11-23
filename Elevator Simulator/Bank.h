#ifndef BANK_H
#define BANK_H

#include <future>

#include "Elevator.h"

class IBank {
    public:
    friend std::ostream& operator<<(std::ostream&, const IBank&);
    virtual std::future<IElevator*> ReceivePassenger(const IPassenger&) = 0;
};

#endif // BANK_H
