#ifndef BANK_H
#define BANK_H

#include <future>

#include "Elevator.h"

class IBank {
    public:
    friend std::ostream& operator<<(std::ostream& os, const IBank& bank);
    virtual std::future<IElevator*> CallElevator(int floor) = 0;
};

#endif // BANK_H
