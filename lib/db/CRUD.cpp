//
// Created by katussska on 4/1/24.
//
#include "CRUD.h"


//TODO: predelat v db budget na budget
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
    SQLite::Statement checkQuery(db, "SELECT COUNT(*) FROM Category WHERE name = ?");
    checkQuery.bind(1, category.getName());
    checkQuery.executeStep();

    if (checkQuery.getColumn(0).getInt() > 0) {
        std::cerr << "Category with the same name already exists." << std::endl;
        return;
    }

    SQLite::Statement insertQuery(db, "INSERT INTO Category (name, budget, budgetSet) VALUES (?, ?, ?)");
    insertQuery.bind(1, category.getName());
    insertQuery.bind(2, category.getBudget());
    insertQuery.bind(3, category.isBudgetSet());
    insertQuery.exec();
}

void createAccount(const Account &account) {
    SQLite::Statement checkQuery(db, "SELECT COUNT(*) FROM Account WHERE name = ?");
    checkQuery.bind(1, account.getName());
    checkQuery.executeStep();

    if (checkQuery.getColumn(0).getInt() > 0) {
        std::cerr << "Account with the same name already exists." << std::endl;
        return;
    }

    SQLite::Statement insertQuery(db, "INSERT INTO Account (name, balance) VALUES (?, ?)");
    insertQuery.bind(1, account.getName());
    insertQuery.bind(2, account.getBalance());
    insertQuery.exec();
}

void createTransaction(std::string type, int accountID, const Transaction &income) {
    SQLite::Statement query(db,
                            "INSERT INTO Transaction(type, amount, description, category_id, account_id, date) "
                            "VALUES (?, ?, ?, ?, ?, ?)");
    query.bind(1, type);
    query.bind(2, income.getAmount());
    query.bind(3, income.getDescription());
    query.bind(4, NULL);
    query.bind(5, accountID);
    query.bind(6, income.getDate());

    if (query.exec())
        std::cout << "Transaction with name '" << income.getDescription() << "' was added." << std::endl;
    else
        std::cerr << "Failed to add transaction '" << income.getDescription() << "'." << std::endl;
}

void createTransaction(const std::string &type, int accountID, int categoryId, const Transaction &expense) {
    SQLite::Statement query(db,
                            "INSERT INTO Transaction(type, amount, description, category_id, account_id, date) "
                            "VALUES (?, ?, ?, ?, ?, ?)");
    query.bind(1, type);
    query.bind(2, expense.getAmount());
    query.bind(3, expense.getDescription());
    query.bind(4, categoryId);
    query.bind(5, accountID);
    query.bind(6, expense.getDate());

    if (query.exec())
        std::cout << "Transaction with name '" << expense.getDescription() << "' was added." << std::endl;
    else
        std::cerr << "Failed to add transaction '" << expense.getDescription() << "'." << std::endl;
}

void eraseCategory(int id) {
    SQLite::Statement query(db, "DELETE FROM Category WHERE id = ?");
    query.bind(1, id);

    if (query.exec())
        std::cout << "Category with ID '" << id << "' deleted successfully." << std::endl;
    else
        std::cerr << "Failed to delete category with ID '" << id << "'." << std::endl;
}

void eraseAccount(int id) {
    SQLite::Statement query(db, "DELETE FROM Account WHERE id = ?");
    query.bind(1, id);

    if (query.exec())
        std::cout << "Account with ID '" << id << "' deleted successfully." << std::endl;
    else
        std::cerr << "Failed to delete account with ID '" << id << "'." << std::endl;
}