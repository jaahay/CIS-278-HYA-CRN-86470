#include <cassert>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

#include "Elevator.h"

class TestElevator : public Elevator {
    public:
    TestElevator() : Elevator(0, 0) {}
};

class TestPassenger : public Passenger {
    public:
    TestPassenger() : Passenger(1, 2) {}
};

void test_equality() {
    TestElevator elevator1;
    TestElevator elevator2;
    assert(elevator1 == elevator2);
    std::cout << "Test equality passed." << std::endl;
}

void test_elevator_initial_state() {
    TestElevator elevator;
    assert(elevator.IsIdle());
    std::cout << "Test initial state passed." << std::endl;
}

void test_passed_origin() {
    TestElevator elevator;
    TestPassenger passenger;
    assert(PassedOrigin(elevator, passenger) == false);
    std::cout << "Test passed origin passed." << std::endl;
}

void test_passed_destination() {
    TestElevator elevator;
    TestPassenger passenger;
    assert(PassedDestination(elevator, passenger) == false);
    std::cout << "Test passed destination passed." << std::endl;
}

void test_elevator_divergence() {
    TestElevator elevator;
    TestPassenger passenger;
    double divergence = elevator.Divergence(passenger);
    assert(divergence >= 0.0);
    std::cout << "Test divergence passed." << std::endl;
}

void test_receive_passenger() {
    TestElevator elevator;
    TestPassenger passenger;
    auto futurePassengers = elevator.ReceivePassenger(passenger);
    auto passengers = futurePassengers.get();
    assert(passengers.size() == 1);
    auto *p = passengers.front();
    assert(passenger == *p);
    auto q = elevator.Wait();
    q.get();


    std::cout << "Test receive passenger passed." << std::endl;
}

int main() {
    test_equality();
    test_elevator_initial_state();
    test_passed_origin();
    test_passed_destination();
    test_elevator_divergence();
    test_receive_passenger();
    return 0;
}