//
// Created by katussska on 3/26/24.
//

#ifndef PROJECT_TRANSACTION_H
#define PROJECT_TRANSACTION_H

#include "FinancialEntity.h"

class Transaction {
protected:
    Account *account;
    double amount;
    std::string description;
    std::time_t date; // :TODO udelat time class nebo nejakou knihovnu na to, std::time?

public:
    Transaction(Account *account, double amount, std::string date) :
            account(account), amount(amount), date(std::move(date)) {}

    Transaction(Account *account, double amount, std::string description, std::string date)
            : account(account), amount(amount), description(std::move(description)), date(std::move(date)) {}

    double getAmount() const;

    std::string getDescription() const;

    std::string getDate() const;

    void setAmount() const;

    void setDescription() const;

    void setDate() const;
};

class Expense : public Transaction {
private:
    Category *category;
public:
    Expense(Account *account, Category *category, double amount, std::string date);

    Expense(Account *account, Category *category, double amount, std::string description, std::string date);

    Category *getCategory() const;

    void setCategory(Category *newCategory);
};

class Income : public Transaction {
public:
    Income(Account *account, double amount, const std::string &date);

    Income(Account *account, double amount, const std::string &description, const std::string &date);
};

#endif //PROJECT_TRANSACTION_H
