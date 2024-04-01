#include "../include/BudgetTracker.h"

int main() {
    // Create/open the SQLite database file
    SQLite::Database db("database.db", SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);

    // Read SQL schema file
    std::ifstream schemaFile("schema.sql");
    std::string schemaSql((std::istreambuf_iterator<char>(schemaFile)),
                          std::istreambuf_iterator<char>());

    // Execute SQL commands to create schema
    try {
        db.exec(schemaSql);
        std::cout << "Schema created successfully." << std::endl;
    } catch (SQLite::Exception &e) {
        std::cerr << "Error executing SQL commands: " << e.what() << std::endl;
        return 1; // Exit with error
    }

    return 0; // Exit successfully
}
