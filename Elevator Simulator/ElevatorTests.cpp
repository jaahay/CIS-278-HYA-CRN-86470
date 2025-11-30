#include <cassert>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

#include "Elevator.cpp"
#include "Passenger.cpp"

class TestElevator : public Elevator {
    public:
    TestElevator() : Elevator(0, 0) {}
};

class TestPassenger : public Passenger {
    public:
    TestPassenger() : Passenger(1, 2) {}
};

void test_elevator_initial_state() {
    TestElevator elevator;
    assert(elevator.IsIdle());
    assert(elevator.CurrentFloor() == 1);
    std::cout << "Test initial state passed." << std::endl;
}

void test_passed_origin() {
    TestElevator elevator;
    const TestPassenger passenger;
    assert(PassedOrigin(elevator, passenger) == false);
    std::cout << "Test passed origin passed." << std::endl;
}

void test_passed_destination() {
    TestElevator elevator;
    const TestPassenger passenger;
    assert(PassedDestination(elevator, passenger) == false);
    std::cout << "Test passed destination passed." << std::endl;
}

void test_elevator_divergence() {
    TestElevator elevator;
    const TestPassenger passenger;
    double divergence = elevator.Divergence(passenger);
    assert(divergence >= 0.0);
    std::cout << "Test divergence passed." << std::endl;
}

void test_receive_passenger() {
    TestElevator elevator;
    const TestPassenger passenger;
    auto futurePassengers = elevator.ReceivePassenger(passenger);
    auto passengers = futurePassengers.get();
    assert(passengers.size() == 1);
    auto *p = passengers.front();
    assert(passenger == *p);

    

    std::cout << "Test receive passenger passed." << std::endl;
    // assert()
}


// void test_elevator_move() {
//     Elevator elevator;
//     int targetFloor = 5;
//     elevator.MoveToFloor(targetFloor);
//     assert(elevator.CurrentFloor() == targetFloor);
//     assert(elevator.IsIdle());
//     std::cout << "Test move to floor passed." << std::endl;
// }

// void test_elevator_invalid_floor() {
//     Elevator elevator;
//     bool exceptionThrown = false;
//     try {
//         elevator.MoveToFloor(0); // Invalid floor
//     } catch (const std::invalid_argument&) {
//         exceptionThrown = true;
//     }
//     assert(exceptionThrown);
//     std::cout << "Test invalid floor passed." << std::endl;
// }

// void test_elevator_concurrent_move() {
//     Elevator elevator = Elevator(5000); // Slow down for testing
//     std::future<int> moveToThirdFloor = elevator.MoveToFloor(3);
//     bool exceptionThrown = false;
//     try {
//         std::future<int> moveToFifthFloor = elevator.MoveToFloor(5); // Attempt to move while already moving
//     } catch (const std::logic_error&) {
//         exceptionThrown = true;
//     }
//     assert(exceptionThrown);
//     std::cout << "Test concurrent move passed." << std::endl;
// }

int main() {
    // test_elevator_initial_state();
    // test_passed();
    // test_elevator_divergence();
    test_receive_passenger();

    // test_elevator_move();
    // test_elevator_invalid_floor();
    // test_elevator_concurrent_move();
    return 0;
}