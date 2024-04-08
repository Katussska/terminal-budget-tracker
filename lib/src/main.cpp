#include "../include/BudgetTracker.h"

int main() {

    createSchema();

    //deleteAccount(1);

    addAccount("mBank", 10000);

//    deleteCategory(6);
//    deleteCategory(7);

    addCategory("fun", 1000);
    addCategory("gas");

//    addTransaction("income", 1, 0, 5000, "paycheck", "20.03.2024");
//    addTransaction("expense", 1, 1, -150, "pub", "20.03.2024");

    return 0;
}
