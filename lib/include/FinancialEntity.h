//
// Created by katussska on 3/26/24.
//

#ifndef PROJECT_FINANCIALENTITY_H
#define PROJECT_FINANCIALENTITY_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <sqlite3.h>
#include <ctime>

class FinancialEntity {
protected:
    std::string name;
    double money{}; // for Category amount money spent in it, for Account its balance

public:
    explicit FinancialEntity(std::string &&name)
            : name(name) {}

    FinancialEntity(std::string &&name, double amount)
            : name(name), money(amount) {}

    std::string getName() const;

    void setName(const std::string &newName);

    double getAmount() const;

};

class Category : public FinancialEntity {
private:
    double budget{};
    bool budgetSet = false;
public:
    Category(const std::string name);

    Category(const std::string name, double limit);

    double getLimit() const;

    void setLimit(double newLimit);
};

class Account : public FinancialEntity {
public:
    Account(const std::string name, double balance);

    void setBalance(double newBalance);

    void deposit(double amount);

    void deposit(double amount, Account *account); // prevest z jineho uctu

    void withdraw(double amount);
};

#endif //PROJECT_FINANCIALENTITY_H