//
// Created by katussska on 3/26/24.
//

#ifndef PROJECT_FINANCIALENTITY_H
#define PROJECT_FINANCIALENTITY_H

#include <SQLiteCpp/SQLiteCpp.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <utility>
#include <sqlite3.h>
#include <stdexcept>
#include <ctime>

class Category {
private:
    std::string name;
    double budget;
    bool budgetSet = false;
public:
    explicit Category(std::string name) :
            name(std::move(name)) {}

    Category(std::string name, double budget) :
            name(std::move(name)), budget(budget), budgetSet(true) {}

    [[nodiscard]] std::string getName() const {
        std::string formattedName = name;

        if (!formattedName.empty())
            formattedName[0] = std::toupper(formattedName[0]);

        return formattedName;
    }

    void setName(const std::string &newName) {
        name = newName;
    }

    [[nodiscard]] double getBudget() const {
        if (budgetSet)
            return budget;
        else {
            return 0;
        }
    }

    [[nodiscard]] bool isBudgetSet() const {
        return budgetSet;
    }

    void setBudget(double newBudget) {
        budget = newBudget;
        budgetSet = true;
    }
};

class Account {
private:
    std::string name;
    double balance;
public:
    Account(std::string name, double balance) : name(std::move(name)), balance(balance) {}

    [[nodiscard]] std::string getName() const {
        std::string formattedName = name;

        if (!formattedName.empty())
            formattedName[0] = std::toupper(formattedName[0]);

        return formattedName;
    }

    void setName(const std::string &newName) {
        name = newName;
    }

    [[nodiscard]] double getBalance() const {
        return balance;
    }

    void setBalance(double newBalance) {
        balance = newBalance;
    }

    void deposit(double amount) {
        if (amount <= 0)
            std::cout << "Deposit must be at least 1 dollar";
        else
            balance += amount;
    }

    void deposit(double amount, Account *account) {// prevest z jineho uctu
        account->withdraw(amount);
        balance += amount;
    }

    void withdraw(double amount) {
        balance -= amount;
    }
};

#endif //PROJECT_FINANCIALENTITY_H