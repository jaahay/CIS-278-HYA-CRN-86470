#ifndef BANK_H
#define BANK_H

#include <future>

#include "Elevator.h"
#include "Passenger.h"

class IBank {
    public:
    virtual std::future<IElevator*> ReceivePassenger(IPassenger*) = 0;
};

#endif // BANK_H
