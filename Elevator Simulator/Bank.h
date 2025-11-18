#ifndef BANK_H
#define BANK_H

#include "Elevator.h"

class Bank {
    public:
        virtual Elevator* CallElevator(int floor) const = 0;
};

#endif // BANK_H
