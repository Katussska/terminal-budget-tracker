//
// Created by katussska on 3/26/24.
//

#include <utility>

#include "../include/BudgetTracker.h"

/// Methods for managing transactions
void addTransaction(std::string type, int accountID, double amount, std::string date) {
    Transaction newIncome{amount, std::move(date)};
    createTransaction(type, accountID, newIncome);
}

void addTransaction(std::string type, int accountID, double amount, std::string description, std::string date) {
    Transaction newIncome{amount, std::move(description), std::move(date)};
    createTransaction(type, accountID, newIncome);
}

void
addTransaction(std::string type, int accountID, int categoryId, double amount, std::string description,
               std::string date) {
    Transaction newExpense{amount, std::move(description), std::move(date)};
    createTransaction(type, accountID, categoryId, newExpense);
}

void addTransaction(std::string type, int accountID, int categoryId, double amount, std::string date) {
    Transaction newExpense{amount, std::move(date)};
    createTransaction(type, accountID, categoryId, newExpense);
}


/// Methods for managing budget categories
void addCategory(std::string name) {
    Category newCategory{name};
    createCategory(newCategory);
}

void addCategory(std::string name, double limit) {
    Category newCategory{name, limit};
    createCategory(newCategory);
}

//void editCategory(std::string name) {}
//
//void editCategory(double budget) {}
//
//void editCategory(std::string name, double budget) {}
//
void deleteCategory(int id) {
    eraseCategory(id);
}

/// Methods for managing accounts
void addAccount(std::string name, double balance) {
    Account newAccount{name, balance};
    createAccount(newAccount);
}

//void editAccount(std::string name) {}
//
//void editAccount(double balance) {}
//
//void editAccount(std::string name, double balance) {}
//
void deleteAccount(int id) {
    eraseAccount(id);
}
