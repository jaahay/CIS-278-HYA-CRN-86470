#include <iostream>
#include "Bank.cpp"

int main() {
    try {
        Bank* bank = new BankImpl(10, 3); // 10 floors, 3 elevators

        Elevator* elevator1 = bank->CallElevator(5);
        std::cout << "Elevator 1 called to floor 5, current floor: " << elevator1->GetCurrentFloor() << std::endl;

        Elevator* elevator2 = bank->CallElevator(8);
        std::cout << "Elevator 2 called to floor 8, current floor: " << elevator2->GetCurrentFloor() << std::endl;

        Elevator* elevator3 = bank->CallElevator(2);
        std::cout << "Elevator 3 called to floor 2, current floor: " << elevator3->GetCurrentFloor() << std::endl;

        delete bank;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}