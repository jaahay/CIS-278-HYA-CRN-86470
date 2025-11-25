#include "Bank.cpp"

int main() {

    bool running = true;

    while (running)
    {
        int numFloors, numElevators;
        std::cout << "Enter number of floors: ";
        std::cin >> numFloors;
        std::cout << "Enter number of elevators: ";
        std::cin >> numElevators;
        std::vector<IElevator *> elevators(numElevators);
        for(int i = 0; i < numElevators; ++i) {
            elevators.at(i) = new Elevator();
        }
        Bank bank(elevators, numFloors);

        std::thread monitorThread([&bank]() {
            while (true) {
                std::this_thread::sleep_for(std::chrono::seconds(10));
                std::cout << std::endl << "Elevator bank status:" << std::endl;
                bank.print(std::cout);
                std::cout << std::endl;
            }
        });
        monitorThread.detach();

        bool calling = true;
        while (true)
        {
            int embark, disembark;
            std::cout << "Board:" << std::endl;
            std::cin >> embark;
            // std::cin >> embark >> disembark;
            std::cout << "Destination:" << std::endl;
            std::cin >> disembark;
            if (embark == 0 || disembark == 0) {
                std::cout << "You've entered 0. Detaching from current simulation." << std::endl;
                calling = false;
                break;
            }

            if(embark < 1 || embark > numFloors) {
                std::cout << "Please embark from a valid floor between 1 and " << numFloors << ".";
            }
            if(disembark < 1 || disembark > numFloors) {
                std::cout << "Please disembark from a valid floor between 1 and " << numFloors << ".";
            }

            // std::thread receivePassenger([&bank, &embark, &disembark]() {
                Passenger passenger(embark, disembark);
                // const IPassenger* p = &passenger;
                // std::cout << std::endl << "Searching for an idle elevator to service ";
                passenger.print(std::cout);
                std::cout << "..." << std::endl;
                auto elevator = &(bank.ReceivePassenger(passenger));
                // std::cout << it << std::endl;
                // auto f = bank.ReceivePassenger(passenger);
                // auto elevator = f.get();
                // std::cout << "Elevator selected to service ";
                // passenger.print(std::cout);
                std::cout << "." << std::endl;
                // std::cout << "It'll cost approx " << elevator->Divergence(passenger) << "." << std::endl;
            // });
            // receivePassenger.detach();
            std::cout << "Next!" << std::endl;
        }
        std::cout << "ok!" << std::endl;
        char continueChoice;
        std::cout << "Do you want to configure another bank? (y/n): " << std::endl;
        std::cin >> continueChoice;
        if (continueChoice != 'y' && continueChoice != 'Y') {
            running = false;
            std::cout << "Exiting Elevator Simulator. Goodbye!" << std::endl;
        }
    }
    
    return 0;
}