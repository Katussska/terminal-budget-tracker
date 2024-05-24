#include "../include/CommandProcessor.h"

int main() {
    createSchema();

    CommandProcessor::printHelp();

    while (true) {
        system("clear");
        std::cout << "Enter command: ";
        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command, entity;
        if (!(iss >> command >> entity)) {
            if (!line.empty()) {
                std::cerr << "Invalid input. Please enter a command and an entity.\n";
                std::this_thread::sleep_for(std::chrono::duration<double>(0.1));
            }
            continue;
        }

        if (command == "exit")
            return 0;

        if (command == "help")
            CommandProcessor::printHelp();

        CommandProcessor::processCommand(command, entity);

        std::this_thread::sleep_for(std::chrono::duration<double>(0.1));
    }
}