#include "../include/BudgetTracker.h"

int main() {
    try {
        // Získání instance třídy Database
        DB *dbInstance = DB::getInstance();

        // Získání připojení k databázi
        SQLite::Database &db = dbInstance->getConnection();

    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
