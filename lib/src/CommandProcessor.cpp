//
// Created by katussska on 5/24/24.
//

#include "../include/CommandProcessor.h"
#include <iostream>

void CommandProcessor::processCommand(const std::string &command, const std::string &entity) {
    if (command == "add") {
        addEntity(entity);
    } else if (command == "delete") {
        deleteEntity(entity);
    } else if (command == "get") {
        getEntity(entity);
    } else if (command == "help") {
        printHelp();
    } else {
        std::cerr << "Invalid command.\n";
    }
}

void CommandProcessor::addEntity(const std::string &entity) {
    if (entity == "category") {
        std::string name;
        double limit = 0.0;
        std::cout << "Enter category name: ";
        std::cin.ignore();  // Ignore the newline character in the input buffer
        std::getline(std::cin, name);
        std::cout << "Enter category limit (optional, enter 0 if no limit): ";
        while (!(std::cin >> limit) || limit > std::numeric_limits<double>::max()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }

        addCategory(name, limit);

    } else if (entity == "account") {
        std::string name;
        double balance = 0.0;
        std::cout << "Enter account name: ";
        std::cin.ignore();  // Ignore the newline character in the input buffer
        std::getline(std::cin, name);
        std::cout << "Enter initial balance: ";
        while (!(std::cin >> balance) || balance > std::numeric_limits<double>::max()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }

        addAccount(name, balance);

    } else if (entity == "transaction") {
        std::string type;
        int accountId;
        int categoryId = 0; // optional
        double amount;
        std::string description;
        std::string date;

        std::cout << "Enter transaction type ('income' or 'expense'): ";
        std::cin.ignore();  // Ignore the newline character in the input buffer
        std::getline(std::cin, type);
        getAllAccountsWithBalance();
        std::cout << "Enter account ID: ";
        while (!(std::cin >> accountId)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }
        getAllCategoriesWithExpenses();
        std::cout << "Enter category ID (optional, enter 0 if no category): ";
        while (!(std::cin >> categoryId)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }
        std::cout << "Enter amount: ";
        while (!(std::cin >> amount) || amount > std::numeric_limits<double>::max()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }
        std::cout << "Enter description: ";
        std::cin.ignore();  // Ignore the newline character in the input buffer
        std::getline(std::cin, description);
        std::cout << "Enter date (DD-MM-YYYY): ";
        std::cin.ignore();  // Ignore the newline character in the input buffer
        std::getline(std::cin, date);

        addTransaction(type, accountId, categoryId, amount, description, date);
    } else {
        std::cerr << "Invalid entity. Please enter 'category', 'account', or 'transaction'.\n";
        printHelp();
    }
}

void CommandProcessor::deleteEntity(const std::string &entity) {
    int id;
    if (entity == "category") {
        getAllCategoriesWithExpenses();
        std::cout << "Enter category ID to delete: ";
        while (!(std::cin >> id)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }
        deleteCategory(id);
    } else if (entity == "account") {
        getAllAccountsWithBalance();
        std::cout << "Enter account ID to delete: ";
        while (!(std::cin >> id)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }
        deleteAccount(id);
    } else if (entity == "transaction") {
        std::string type;
        int accountId;
        int categoryId = 0; // optional
        double amount;
        std::string description;
        std::string date;

        std::cout << "Enter transaction type ('income' or 'expense'): ";
        std::cin.ignore();  // Ignore the newline character in the input buffer
        std::getline(std::cin, type);
        getAllAccountsWithBalance();
        std::cout << "Enter account ID: ";
        while (!(std::cin >> accountId) || accountId > std::numeric_limits<int>::max() || std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }
        getAllCategoriesWithExpenses();
        std::cout << "Enter category ID (optional, enter 0 if no category): ";
        while (!(std::cin >> categoryId) || categoryId > std::numeric_limits<int>::max() || std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }
        std::cout << "Enter amount: ";
        while (!(std::cin >> amount) || amount > std::numeric_limits<double>::max() || std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }
        std::cout << "Enter description: ";
        std::cin.ignore();  // Ignore the newline character in the input buffer
        std::getline(std::cin, description);
        std::cout << "Enter date (DD.MM.YYYY): ";

// Date validation function
        auto isValidDate = [](const std::string &date) {
            std::regex datePattern(R"((\d{2})\.(\d{2})\.(\d{4}))");
            std::smatch match;
            if (!std::regex_match(date, match, datePattern)) {
                return false;
            }

            int day = std::stoi(match[1]);
            int month = std::stoi(match[2]);
            int year = std::stoi(match[3]);

            if (year < 2000 || year > 2050) {
                return false;
            }

            if (month < 1 || month > 12) {
                return false;
            }

            int daysInMonth = 31;
            switch (month) {
                case 4:
                case 6:
                case 9:
                case 11:
                    daysInMonth = 30;
                    break;
                case 2:
                    daysInMonth = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
                    break;
            }

            return day >= 1 && day <= daysInMonth;
        };

        std::cin >> date;

        while (!isValidDate(date)) {
            std::cout << "Invalid date format or value. Please enter date (DD.MM.YYYY): ";
            std::cin >> date;
        }

        addTransaction(type, accountId, categoryId, amount, description, date);
    } else {
        std::cerr << "Invalid entity. Please enter 'category', 'account', or 'transaction'.\n";
        printHelp();
    }
}

void CommandProcessor::getEntity(const std::string &entity) {
    if (entity == "categories") {
        getAllCategoriesWithExpenses();
    } else if (entity == "accounts") {
        getAllAccountsWithBalance();
    } else if (entity == "transactions") {
        getTransactions("all");
    } else if (entity == "incomes") {
        getTransactions("income");
    } else if (entity == "expenses") {
        getTransactions("expense");
    } else if (entity == "transaction") {
        int id;
        std::cout << "Enter transaction ID: ";
        while (!(std::cin >> id)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }
        getTransactionsByCategoryId(id);
    } else if (entity == "category") {
        getAllCategoriesWithExpenses();
        int id;
        std::cout << "Enter category ID: ";
        while (!(std::cin >> id)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }
        getTransactionsByCategoryId(id);
    } else if (entity == "account") {
        getAllAccountsWithBalance();
        int id;
        std::cout << "Enter account ID: ";
        while (!(std::cin >> id)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }
        getAccountDetailsById(id);
    } else {
        std::cerr
                << "Invalid entity. Please enter 'categories', 'accounts', 'income', 'expense', 'transaction', 'category', or 'account'.\n";
        printHelp();
    }
}

void CommandProcessor::printHelp() {
    std::cout << "\nAvailable commands:\n\n";
    std::cout << "  add: \n";
    std::cout << "    - Add a new entity. Available entities are 'category', 'account', and 'transaction'.\n";
    std::cout << "    - After this command, you will be asked additional questions to complete the function.\n";
    std::cout << "    - For 'category', you will be asked to enter the category name and limit.\n";
    std::cout << "    - For 'account', you will be asked to enter the account name and initial balance.\n";
    std::cout
            << "    - For 'transaction', you will be asked to enter the transaction type, account ID, category ID, amount, description, and date.\n\n";
    std::cout << "  delete: \n";
    std::cout << "    - Delete an existing entity. Available entities are 'category', 'account', and 'transaction'.\n";
    std::cout << "    - After this command, you will be asked to enter the ID of the entity you want to delete.\n\n";
    std::cout << "  get: \n";
    std::cout
            << "    - Get information about an entity. Available entities are 'categories', 'accounts', 'transactions', 'incomes', 'expenses', 'transaction', 'category', and 'account'.\n";
    std::cout << "    - After this command, you will be asked additional questions to complete the function.\n";
    std::cout
            << "    - For 'transaction', 'category', and 'account', you can specify 'ID' or 'NAME' to get information by ID or name.\n\n";
    std::cout << "  help: \n";
    std::cout << "    - Display this help message.\n\n";
    std::cout << "For 'add', 'delete', and 'get' commands, you will be prompted to enter additional information.\n\n";
}
