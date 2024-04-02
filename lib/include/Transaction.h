//
// Created by katussska on 3/26/24.
//

#ifndef PROJECT_TRANSACTION_H
#define PROJECT_TRANSACTION_H

#include <utility>

#include "FinancialEntity.h"

class Transaction {
protected:

    Account *account;
    double amount;
    std::string description;
    std::string date;

public:
    explicit Transaction(Account *account, double amount, std::string date) :
            account(account), amount(amount), date(std::move(date)) {}

    Transaction(Account *account, double amount, std::string description, std::string date)
            : account(account), amount(amount), description(std::move(description)), date(std::move(date)) {}

    [[nodiscard]] double getAmount() const {
        return amount;
    }

    [[nodiscard]] std::string getDescription() const {
        return description;
    }

    [[nodiscard]] std::string getDate() const {
        return date;
    }

    static void setAmount(double amount) {
        amount = amount;
    }

    void setDescription(std::string desc) {
        description = std::move(desc);
    }

    void setDate(std::string d) {
        date = std::move(d);
    }
};

class Expense : public Transaction {
private:
    Category *category = nullptr;
public:
    explicit Expense(Account *account, double amount, std::string date)
            : Transaction(account, amount, std::move(date)) {}


    explicit Expense(Account *account, Category *category, double amount, std::string date)
            : Transaction(account, amount, std::move(date)), category(category) {}

    explicit Expense(Account *account, double amount, std::string description, std::string date)
            : Transaction(account, amount, std::move(description), std::move(date)) {}

    Expense(Account *account, Category *category, double amount, std::string description, std::string date)
            : Transaction(account, amount, std::move(description), std::move(date)), category(category) {}

    [[nodiscard]] Category *getCategory() const {
        return category;
    }

    void setCategory(Category *newCategory) {
        category = newCategory;
    }
};

class Income : public Transaction {
public:
    explicit Income(Account *account, double amount, std::string date)
            : Transaction(account, amount, std::move(date)) {}

    Income(Account *account, double amount, std::string description, std::string date)
            : Transaction(account, amount, std::move(description), std::move(date)) {}
};

#endif //PROJECT_TRANSACTION_H
