//
// Created by katussska on 5/24/24.
//

#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include "BudgetTracker.h"
#include <string>

class CommandProcessor {
public:
    static void processCommand(const std::string &command, const std::string &entity);

    static void printHelp();

private:
    static void addEntity(const std::string &entity);

    static void deleteEntity(const std::string &entity);

    static void getEntity(const std::string &entity);

};

#endif // COMMAND_PROCESSOR_H
