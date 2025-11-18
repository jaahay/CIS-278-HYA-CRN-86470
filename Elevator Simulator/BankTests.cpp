#include <cassert>
#include <iostream>
#include "Bank.cpp"

void test_bank_call_elevator() {
    BankImpl bank(10, 2); // 10 floors, 2 elevators

    Elevator* elevator = bank.CallElevator(5);
    assert(elevator != nullptr);
    std::cout << "Test CallElevator to floor 5 passed. Elevator current floor: " << elevator->GetCurrentFloor() << std::endl;
}

void test_bank_invalid_floor() {
    BankImpl bank(10, 2); // 10 floors, 2 elevators

    try {
        bank.CallElevator(0); // Invalid floor
        assert(false); // Should not reach here
    } catch (const std::out_of_range&) {
        std::cout << "Test CallElevator to invalid floor 0 passed." << std::endl;
    }

    try {
        bank.CallElevator(11); // Invalid floor
        assert(false); // Should not reach here
    } catch (const std::out_of_range&) {
        std::cout << "Test CallElevator to invalid floor 11 passed." << std::endl;
    }
}

void test_bank_multiple_calls() {
    BankImpl bank(10, 2); // 10 floors, 2 elevators

    Elevator* elevator1 = bank.CallElevator(7);
    assert(elevator1 != nullptr);
    std::cout << "First CallElevator to floor 7 passed. Elevator current floor: " << elevator1->GetCurrentFloor() << std::endl;

    Elevator* elevator2 = bank.CallElevator(2);
    assert(elevator2 != nullptr);
    std::cout << "Second CallElevator to floor 2 passed. Elevator current floor: " << elevator2->GetCurrentFloor() << std::endl;

    assert(elevator1 != elevator2); // Should be different elevators
    std::cout << "Test multiple CallElevator calls passed." << std::endl;
}

void test_bank_elevator_movement() {
    BankImpl bank(10, 2); // 10 floors, 2 elevators

    Elevator* elevator = bank.CallElevator(4);
    assert(elevator != nullptr);
    elevator->MoveToFloor(4);
    assert(elevator->GetCurrentFloor() == 4);
    std::cout << "Test CallElevator and MoveToFloor to floor 4 passed. Elevator current floor: " << elevator->GetCurrentFloor() << std::endl;
}

int main() {
    test_bank_call_elevator();
    test_bank_invalid_floor();
    test_bank_multiple_calls();
    test_bank_elevator_movement();
    return 0;
}