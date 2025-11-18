#include <cassert>
#include <iostream>
#include "Elevator.cpp"

void test_elevator_initial_state() {
    Elevator elevator;
    assert(elevator.GetCurrentFloor() == 1);
    assert(elevator.IsIdle());
    std::cout << "Test initial state passed." << std::endl;
}

void test_elevator_move() {
    Elevator elevator;
    int targetFloor = 5;
    elevator.MoveToFloor(targetFloor);
    assert(elevator.GetCurrentFloor() == targetFloor);
    assert(elevator.IsIdle());
    std::cout << "Test move to floor passed." << std::endl;
}

void test_elevator_invalid_floor() {
    Elevator elevator;
    bool exceptionThrown = false;
    try {
        elevator.MoveToFloor(0); // Invalid floor
    } catch (const std::invalid_argument&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
    std::cout << "Test invalid floor passed." << std::endl;
}

void test_elevator_concurrent_move() {
    Elevator elevator = Elevator(5000); // Slow down for testing
    std::future<int> moveToThirdFloor = elevator.MoveToFloor(3);
    bool exceptionThrown = false;
    try {
        std::future<int> moveToFifthFloor = elevator.MoveToFloor(5); // Attempt to move while already moving
    } catch (const std::logic_error&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
    std::cout << "Test concurrent move passed." << std::endl;
}

int main() {
    test_elevator_initial_state();
    test_elevator_move();
    test_elevator_invalid_floor();
    test_elevator_concurrent_move();
    return 0;
}