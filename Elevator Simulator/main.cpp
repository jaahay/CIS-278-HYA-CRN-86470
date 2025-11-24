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
        Bank bank(numFloors, numElevators);

        std::thread monitorThread([&]() {
            while (true) {
                std::cout << std::endl << "Elevator bank status:" << std::endl;
                std::cout << b << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(10));
            }
        });
        monitorThread.detach();

        bool calling = true;
        while (calling)
        {
            int embark, disembark;
            std::cout << "Enter from and to floors separated by a space:\n\tEnter 0 to exit." << std::endl;
            std::cin >> embark >> disembark;
            if (embark == 0 || disembark == 0) {
                std::cout << "You've entered 0. Detaching from current simulation." << std::endl;
                calling = false;
                continue;
            }

            if(embark < 1 || embark > numFloors) {
                std::cout << "Please embark from a valid floor between 1 and " << numFloors << ".";
            }
            if(disembark < 1 || disembark > numFloors) {
                std::cout << "Please disembark from a valid floor between 1 and " << numFloors << ".";
            }

            std::thread receivePassenger([&bank, &embark, &disembark]() {
                Passenger passenger(embark, disembark);
                std::cout << std::endl << "Searching for an idle elevator to service " << passenger << "..." << std::endl;
                IElevator* elevator = bank.ReceivePassenger(&passenger).get();
                std::cout << "Elevator selected to service " << passenger << "." << std::endl;
                std::cout << "It'll cost approx " << elevator->Divergence(&passenger);
            });
            receivePassenger.detach();
        }
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