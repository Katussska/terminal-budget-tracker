//
// Created by katussska on 3/26/24.
//

#ifndef PROJECT_FINANCIALENTITY_H
#define PROJECT_FINANCIALENTITY_H

#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <sqlite3.h>
#include <ctime>

class Category {
private:
    std::string name;
    double limit;
    bool limitSet = false;
public:
    Category(const std::string name);

    Category(const std::string name, double limit);

    std::string getName() const;

    void setName(const std::string &newName);

    double getLimit() const;

    void setLimit(double newLimit);
};

class Account {
    std::string name;
    double balance;
public:
    Account(const std::string name, double balance);

    std::string getName() const;

    void setName(const std::string &newName);

    double getBalance();

    void setBalance(double newBalance);

    void deposit(double amount);

    void deposit(double amount, Account *account); // prevest z jineho uctu

    void withdraw(double amount);
};

#endif //PROJECT_FINANCIALENTITY_H