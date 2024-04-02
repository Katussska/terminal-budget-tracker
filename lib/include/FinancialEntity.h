//
// Created by katussska on 3/26/24.
//

#ifndef PROJECT_FINANCIALENTITY_H
#define PROJECT_FINANCIALENTITY_H

#include "DB.h"

class Category {
private:
    std::string name;
    double limit{};
    bool limitSet = false;
public:
    explicit Category(std::string name) :
            name(std::move(name)) {}

    Category(std::string name, double limit) :
            name(std::move(name)), limit(limit), limitSet(true) {}

    [[nodiscard]] std::string getName() const {
        return name;
    }

    void setName(const std::string &newName) {
        name = newName;
    }

    [[nodiscard]] double getLimit() const {
        if (limitSet)
            return limit;
        else {
            std::cout << "No limit";
            return 0;
        }
    }

    void setLimit(double newLimit) {
        limit = newLimit;
        limitSet = true;
    }
};

class Account {
private:
    std::string name;
    double balance;
public:
    Account(std::string name, double balance) : name(std::move(name)), balance(balance) {}

    [[nodiscard]] std::string getName() const {
        return name;
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