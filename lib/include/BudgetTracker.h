//
// Created by katussska on 3/26/24.
//

#ifndef PROJECT_BUDGETTRACKER_H
#define PROJECT_BUDGETTRACKER_H

#include "../db/CRUD.h"

/// Methods for managing transactions
void addTransaction
        (const std::string &type, int accountID, int categoryId, double amount,
         const std::string &description, const std::string &date);

void editTransaction
        (int id, int accountID, int categoryId, double amount, const std::string &description, const std::string &date);

void deleteTransaction(int id);

/// Methods for managing budget categories
void addCategory(std::string name);

void addCategory(std::string name, double limit);

void editCategory(int id, const std::string &name, double budget);

void deleteCategory(int id);

/// Methods for managing accounts
void addAccount(std::string name, double balance);

void editAccount(int id, std::string name, double balance, double moneyChange);

void deleteAccount(int id);

/// Methods for reading data
void getAllCategoriesWithExpenses();

void getTransactionsByCategoryId(int id);

void getTransactionsByCategoryName(const std::string &name);

void getAllAccountsWithBalance();

void getAccountDetailsById(int id);

void getAccountDetailsByName(const std::string &name);

void getTransactionsByType(const std::string &type);

void getTransactions(const std::string &type);

#endif //PROJECT_BUDGETTRACKER_H
