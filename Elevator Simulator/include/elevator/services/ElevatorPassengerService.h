// elevator/services/ElevatorPassengerService.h
#ifndef ELEVATOR_SERVICES_ELEVATOR_PASSENGER_SERVICE_H
#define ELEVATOR_SERVICES_ELEVATOR_PASSENGER_SERVICE_H

#include "elevator/models/Elevator.h"
#include "elevator/models/Passenger.h"

namespace elevator::services {

    struct PassengerService {

        // Add a passenger to pending list immutably
        static Elevator AddPendingPassenger(const Elevator&, const Passenger&);

        // Calculate inconvenience score (divergence)
        static double Divergence(const Passenger&);

        static bool PassedOrigin(const Elevator& elevator, const Passenger& passenger);

        static bool PassedDestination(const Elevator& elevator, const Passenger& passenger);

        static bool FurtherToGo(const Elevator& elevator);

        static double FarthestToGo(const Elevator& elevator);

        // Returns updated Elevator with passenger boarded
        static Elevator BoardPassengers(const Elevator&);

        // Returns updated Elevator with passengers who leave
        static Elevator PassengersLeave(const Elevator&);

        // todo: doc
        static Elevator HandleBoardingDeparting(const Elevator&);
    };

} // namespace elevator::services

#endif ELEVATOR_SERVICES_ELEVATOR_PASSENGER_SERVICE_H