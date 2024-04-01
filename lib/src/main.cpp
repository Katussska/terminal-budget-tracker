#include "../include/BudgetTracker.h"

int main() {
    // Create/open the SQLite database file in the db directory
    SQLite::Database db("../db/database.db", SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);

    // Read SQL schema file
    std::ifstream schemaFile("../db/schema.sql");
    if (!schemaFile.is_open()) {
        std::cerr << "Error opening schema file." << std::endl;
        return 1;
    }

    std::string schemaSql((std::istreambuf_iterator<char>(schemaFile)),
                          std::istreambuf_iterator<char>());

    try {
        db.exec(schemaSql);
        std::cout << "Schema created successfully." << std::endl;
    } catch (SQLite::Exception &e) {
        std::cerr << "Error executing SQL commands: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
