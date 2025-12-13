#include <cassert>
#include <iostream>

#include "Passenger.cpp"

void test_passenger_initial_state() {
    Passenger passenger(1, 2);
    assert(passenger.Origin() == 1);
    assert(passenger.Destination() == 2);
    assert(passenger.Heading() == GOING_UP);
    std::cout << "Test initial state passed." << std::endl;
}

int main() {
    test_passenger_initial_state();
    return 0;
}