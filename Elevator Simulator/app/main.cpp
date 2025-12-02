#include "../src/Bank.cpp"

static const int MONITOR_BANK_INTERVAL_MS = int(3000);

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

        std::thread monitorThread([&bank, running]() {
            while (running) {
                std::this_thread::sleep_for(std::chrono::milliseconds(MONITOR_BANK_INTERVAL_MS));
                bank.print(std::cout);
                std::cout << std::endl;
            }
        });
        monitorThread.detach();

        bool calling = true;
        while (calling)
        {
            int embark, disembark;
            std::cout << "Board:" << std::endl;
            std::cin >> embark;
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

            Passenger* passenger = new Passenger(embark, disembark);
            auto& elevator = bank.ReceivePassenger(*passenger);
            std::cout << "Next!!" << std::endl;
        }
        running = false;
        char continueChoice;
        std::cout << "Do you want to configure another bank? (y/n): " << std::endl;
        std::cin >> continueChoice;
        if (continueChoice != 'y' && continueChoice != 'Y') {
            running = false;
            std::cout << "Exiting Elevator Simulator. Goodbye!" << std::endl;
        }
        else { running = true; }
    }
    
    return 0;
}