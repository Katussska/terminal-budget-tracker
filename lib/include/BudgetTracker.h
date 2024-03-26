//
// Created by katussska on 3/26/24.
//

#ifndef PROJECT_BUDGETTRACKER_H
#define PROJECT_BUDGETTRACKER_H

#include "Transaction.h"

class BudgetTracker {
private:
//    std::vector<Expense *> expenses;
//    std::vector<Income *> incomes;
//    std::vector<Category *> categories;
//    std::vector<Account *> accounts;

public:
    //TODO: dodelat, nejsou vsechny funkce dodelane ani pro basic pouziti


    std::vector<Transaction *> filter();

    // Methods for managing expenses
    void addExpense(const Expense &expense);

    void editExpense(int index, const Expense &newExpense);

    void deleteExpense(int index);

    // Methods for managing incomes
    void addIncome(const Income &income);

    void editIncome(int index, const Income &newIncome);

    void deleteIncome(int index);

    // Methods for managing budget categories
    void addCategory(const Category &category);

    void editCategory(int index, const Category &newCategory);

    void deleteCategory(int index);

    // Methods for managing accounts
    void addAccount(const Account &account);

    void editAccount(int index, const Account &newAccount);

    void deleteAccount(int index);
};


#endif //PROJECT_BUDGETTRACKER_H
