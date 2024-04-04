//
// Created by katussska on 3/26/24.
//

#include <utility>

#include "../include/BudgetTracker.h"

/// Methods for managing transactions
void addTransaction(const std::string &type, int accountID, double amount, std::string date) {
    Transaction newIncome{amount, std::move(date)};
    createTransaction(type, accountID, newIncome);
}

void addTransaction(const std::string &type, int accountID, double amount, std::string description, std::string date) {
    Transaction newIncome{amount, std::move(description), std::move(date)};
    createTransaction(type, accountID, newIncome);
}

void
addTransaction(const std::string &type, int accountID, int categoryId, double amount, std::string description,
               std::string date) {
    Transaction newExpense{amount, std::move(description), std::move(date)};
    createTransaction(type, accountID, categoryId, newExpense);
}

void addTransaction(const std::string &type, int accountID, int categoryId, double amount, std::string date) {
    Transaction newExpense{amount, std::move(date)};
    createTransaction(type, accountID, categoryId, newExpense);
}

void
editTransaction(int id, int accountID = 0, int categoryId = 0, double amount = 0,
                const std::string &date = "", const std::string &description = "") {
    updateTransaction(id, accountID, categoryId, amount, description, date);
}

void deleteTransaction(int id) {
    destroyTransaction(id);
}

/// Methods for managing budget categories
void addCategory(std::string name) {
    Category newCategory{std::move(name)};
    createCategory(newCategory);
}

void addCategory(std::string name, double limit) {
    Category newCategory{std::move(name), limit};
    createCategory(newCategory);
}

void editCategory(int id, const std::string &name = "", double budget = 0.0) {
    updateCategory(id, name, budget);
}

void deleteCategory(int id) {
    destroyCategory(id);
}

/// Methods for managing accounts
void addAccount(std::string name, double balance) {
    Account newAccount{std::move(name), balance};
    createAccount(newAccount);
}

void editAccount(int id, const std::string &name = "", double balance = 0.0, double moneyChange = 0.0) {
    updateAccount(id, name, balance, moneyChange);
}

void deleteAccount(int id) {
    destroyAccount(id);
}