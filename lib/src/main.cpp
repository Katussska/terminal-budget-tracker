#include "../include/BudgetTracker.h"

int main() {

//    createSchema();

    addAccount("mBank", 10000);

    addCategory("fun", 1000);
    addCategory("gas");

    addTransaction("income", 1, 5000, "paycheck" , "20.03.2024");
    addTransaction("expense", 1, 2, 1000, "20.03.2024");

    return 0;
}
