#ifndef BANK_H
#define BANK_H

#include <future>

#include "Elevator.h"

class IBank {
    public:
    virtual std::future<IElevator*> CallElevator(int floor) const = 0;
    
    virtual void toString(char* buffer, size_t bufferSize) const = 0;
};

#endif // BANK_H
