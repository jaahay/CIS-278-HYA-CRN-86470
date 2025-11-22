#include "Passenger.h"

class Passenger : public IPassenger {
    private:
    int origin;
    int destination;

    public:

    Passenger(int origin = 1, int destination = 1)
        : origin(origin), destination(destination) {}

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