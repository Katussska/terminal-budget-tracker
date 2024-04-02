//
// Created by katussska on 3/26/24.
//

#ifndef COINSHEN_BUDGETTRACKER_H
#define COINSHEN_BUDGETTRACKER_H

#include "../db/CRUD.h"

//TODO: dodelat, nejsou vsechny funkce dodelane ani pro basic pouziti


std::vector<Transaction *> filter();

// Methods for managing expenses
void addExpense();

void editExpense();

void deleteExpense();

// Methods for managing incomes
void addIncome();

void editIncome();

void deleteIncome();

// Methods for managing budget categories
void addCategory();

void editCategory();

void deleteCategory();

// Methods for managing accounts
void addAccount();

void editAccount();

void deleteAccount();


#endif //COINSHEN_BUDGETTRACKER_H
