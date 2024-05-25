//
// Created by katussska on 3/26/24.
//

#ifndef PROJECT_TRANSACTION_H
#define PROJECT_TRANSACTION_H

#include "FinancialEntity.h"

class Transaction {
private:
    double amount;
    std::string description;
    std::string date;
public:
    explicit Transaction(double amount, std::string date) :
            amount(amount), date(std::move(date)) {}

    Transaction(double amount, std::string description, std::string date)
            : amount(amount), description(std::move(description)), date(std::move(date)) {}

    [[nodiscard]] double getAmount() const {
        return amount;
    }

    [[nodiscard]] std::string getDescription() const {
        return description;
    }

    [[nodiscard]] std::string getDate() const {
        return date;
    }
};

#endif //PROJECT_TRANSACTION_H
