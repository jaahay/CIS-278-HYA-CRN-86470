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
        std::thread monitorThread([bank]() {
            while (true) {
                std::cout << std::endl << "Elevator bank status:" << std::endl;
                std::cout << bank << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(10));
            }
        });
        monitorThread.detach();

        bool calling = true;
        while (calling)
        {
            int floor;
            std::cout << "Enter the floor number to call the elevator (1-" << numFloors << "), or 0 to exit:";
            std::cin >> floor;
            std::cout << std::endl;
            if (floor == 0) {
                calling = false;
                continue;
            }
            std::thread callElevator([&bank, floor]() {
                bank.CallElevator(floor);
            });
            callElevator.detach();
            std::cout << bank << std::endl;
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