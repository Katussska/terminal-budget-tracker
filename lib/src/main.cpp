#include "../include/CommandProcessor.h"

int main() {
    createSchema();
    system("clear");

    CommandProcessor::printHelp();

    std::string line;
    while (true) {
        std::cout << "Enter command: ";
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command, entity;
        if (!(iss >> command)) {
            if (!line.empty()) {
                std::cerr << "Invalid input. Please enter a command.\n";
                std::this_thread::sleep_for(std::chrono::duration<double>(0.1));
            }
            continue;
        }

        if (command == "exit")
            return 0;

        if (command == "help") {
            CommandProcessor::printHelp();
            continue;
        }

        if (!(iss >> entity)) {
            std::cerr << "Invalid input. Please enter an entity.\n";
            std::this_thread::sleep_for(std::chrono::duration<double>(0.1));
            continue;
        }

        CommandProcessor::processCommand(command, entity);

        std::this_thread::sleep_for(std::chrono::duration<double>(0.1));
    }
}