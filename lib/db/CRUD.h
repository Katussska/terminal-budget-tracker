//
// Created by katussska on 4/2/24.
//

#ifndef PROJECT_CRUD_H
#define PROJECT_CRUD_H

#include "../include/Transaction.h"

// todo: put this in the db class probably
inline SQLite::Database db("../lib/db/database.db", SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);

///CREATE
void createSchema();

void createCategory(const Category &category);

void createAccount(const Account &account);

void createTransaction(std::string type, int accountID, const Transaction &income);

void createTransaction(const std::string &type, int accountID, int categoryId, const Transaction &expense);

///UPDATE
void updateCategory(int id, const std::string &name, double budget);

void updateAccount(int id, const std::string &name, double balance);

void updateTransaction(int id, int accountID, int categoryId, double amount, const std::string &description,
                       std::string date);

///READ
//...

///DELETE
void destroyCategory(int id);

void destroyAccount(int id);


#endif //PROJECT_CRUD_H
