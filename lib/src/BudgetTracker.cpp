//
// Created by katussska on 3/26/24.
//

#include "../include/BudgetTracker.h"

// Methods for managing budget categories
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
//void editCategory(double limit) {}
//
//void editCategory(std::string name, double limit) {}
//
//void deleteCategory(std::string name) {}
//
//// Methods for managing accounts
//void addAccount(std::string name, double balance) {}
//
//void editAccount(std::string name) {}
//
//void editAccount(double balance) {}
//
//void editAccount(std::string name, double balance) {}
//
//void deleteAccount(std::string name) {}
