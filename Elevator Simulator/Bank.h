#ifndef BANK_H
#define BANK_H

#include "Elevator.h"

class Bank {
    protected:
        virtual Elevator* CallElevator() = 0;
};

#endif // BANK_H