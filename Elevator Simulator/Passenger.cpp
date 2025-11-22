#include "Passenger.h"

#include <format>
#include <stdexcept>

class Passenger : public IPassenger {
    private:
    int origin;
    int destination;

    public:

    Passenger(int origin = 1, int destination = 1, int numFloors)
        : origin(origin), destination(destination) {
            if(origin == destination) {
                throw std::invalid_argument("Embark and disembark from two different floors, please.");
            }
            if(origin < 1 || origin > numFloors) {
                throw std::invalid_argument(
                    std::format("Please embark from a valid floor between 1 and {}.", numFloors)
                );
            }
            if(destination < 1 || destination > numFloors) {
                throw std::invalid_argument(
                    std::format("Please disembark from a valid floor between 1 and {}.", numFloors)
                );
            }
        }

    // ~Passenger() {}

    // Passenger(const Passenger& other)
    //     : origin(other.origin), destination(other.destination) {}

    // Passenger& operator=(const Passenger& other) {
    //     if (this != &other) {
    //         origin = other.origin;
    //         destination = other.destination;
    //     }
    //     return *this;
    // }

    // Passenger(Passenger&& other) noexcept
    //     : origin(other.origin), destination(other.destination) {}

    // Passenger& operator=(Passenger&& other) noexcept {
    //     if (this != &other) {
    //         origin = other.origin;
    //         destination = other.destination;
    //     }
    //     return *this;
    // }
    
    friend std::ostream& operator<<(std::ostream&, const Passenger&);

    int Origin() override { return origin; }
    int Destination() override { return destination; }
    
};

std::ostream& operator<<(std::ostream& os, const Passenger& passenger) {
    os << "Origin: " << passenger.origin;
    os << "Destination: " << passenger.destination;
    return os;
}