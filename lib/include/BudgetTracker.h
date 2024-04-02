//
// Created by katussska on 3/26/24.
//

#ifndef PROJECT_BUDGETTRACKER_H
#define PROJECT_BUDGETTRACKER_H

#include "../db/CRUD.h"

////TODO: actually i domyslet, jak bude filter fungovat
////std::vector<Transaction *> filter();
//
//// Methods for managing expenses
//void addExpense();
//
//void editExpense();
//
//void deleteExpense();
//
//// Methods for managing incomes
//void addIncome();
//
//void editIncome();
//
//void deleteIncome();

// Methods for managing budget categories
void addCategory(std::string name);

void addCategory(std::string name, double limit);

//void editCategory(std::string name);
//
//void editCategory(double limit);
//
//void editCategory(std::string name, double limit);
//
//void deleteCategory(std::string name);
//
//// Methods for managing accounts
//void addAccount(std::string name, double balance);
//
//void editAccount(std::string name);
//
//void editAccount(double balance);
//
//void editAccount(std::string name, double balance);
//
//void deleteAccount(std::string name);


#endif //PROJECT_BUDGETTRACKER_H
