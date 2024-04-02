//
// Created by katussska on 4/1/24.
//
#include "CRUD.h"


//TODO: predelat v db budget na limit
void createSchema() {
    std::ifstream schemaFile("../lib/db/schema.sql");
    if (!schemaFile.is_open()) {
        std::cerr << "Error opening schema file." << std::endl;
        throw std::runtime_error("Error opening schema file");
    }

    std::string schemaSql((std::istreambuf_iterator<char>(schemaFile)),
                          std::istreambuf_iterator<char>());

    try {
        db.exec(schemaSql);
        std::cout << "Schema created successfully." << std::endl;
    } catch (SQLite::Exception &e) {
        std::cerr << "Error executing SQL commands: " << e.what() << std::endl;
        throw std::runtime_error("Error executing SQL commands");
    }
}

void createCategory(const Category &category) {
    SQLite::Statement query(db, "INSERT INTO Category (name, budget, budgetSet) VALUE (?, ?, ?)");
    query.bind(1, category.getName());
    query.bind(2, category.getLimit());
    query.bind(3, category.isLimitSet());
    query.exec();
}



