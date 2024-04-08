//
// Created by katussska on 4/1/24.
//
#include "CRUD.h"

///HELPERS
bool recordExists(const std::string &tableName, const std::string &recordName) {
    std::string queryStr = "SELECT COUNT(*) FROM " + tableName + " WHERE name = ?";
    StatementPtr checkQuery(new SQLite::Statement(*db, queryStr));
    checkQuery->bind(1, recordName);
    checkQuery->executeStep();
    return (checkQuery->getColumn(0).getInt() > 0);
}

std::string buildInsertQuery(const std::string &tableName, const std::vector<std::string> &columns,
                             const std::vector<std::string> &values) {
    if (columns.size() != values.size() || columns.empty())
        throw std::invalid_argument("Columns and values must have the same size and cannot be empty.");

    std::stringstream queryBuilder;

    queryBuilder << "INSERT INTO " << tableName << " (";

    for (size_t i = 0; i < columns.size(); ++i) {
        queryBuilder << columns[i];
        if (i != columns.size() - 1)
            queryBuilder << ", ";
    }

    queryBuilder << ") VALUES (";

    for (size_t i = 0; i < values.size(); ++i) {
        queryBuilder << "'" << values[i] << "'";
        if (i != values.size() - 1)
            queryBuilder << ", ";
    }

    queryBuilder << ")";

    return queryBuilder.str();
}

void insertRecord(const std::string &tableName, const std::vector<std::string> &columns,
                  const std::vector<std::string> &values) {
    std::string queryStr = buildInsertQuery(tableName, columns, values);
    try {
        db->exec(queryStr);
        std::cout << "Record inserted successfully into table '" << tableName << "'." << std::endl;
    } catch (SQLite::Exception &e) {
        std::cerr << "Failed to insert record into table '" << tableName << "'. Error: " << e.what() << std::endl;
    }
}

std::string updateQuery(const std::string &tableName, const std::string &attributeName) {
    return "UPDATE " + tableName + " SET " + attributeName + " = ? WHERE id = ?";
}

///CREATE
void createSchema() {
    std::ifstream schemaFile("../lib/db/schema.sql");
    if (!schemaFile.is_open()) {
        std::cerr << "Error opening schema file." << std::endl;
        throw std::runtime_error("Error opening schema file");
    }

    std::string schemaSql((std::istreambuf_iterator<char>(schemaFile)),
                          std::istreambuf_iterator<char>());

    try {
        db->exec(schemaSql);
        std::cout << "Schema created successfully." << std::endl;
    } catch (SQLite::Exception &e) {
        std::cerr << "Error executing SQL commands: " << e.what() << std::endl;
        throw std::runtime_error("Error executing SQL commands");
    }
}

void createCategory(const Category &category) {
    if (recordExists("Category", category.getName())) {
        std::cerr << "Category with the same name already exists." << std::endl;
        return;
    }

    std::vector<std::string> columns = {"name", "budget", "budgetSet"};
    std::vector<std::string> values = {category.getName(), std::to_string(category.getBudget()),
                                       std::to_string(category.isBudgetSet())};

    insertRecord("Category", columns, values);
}

void createAccount(const Account &account) {
    if (recordExists("Account", account.getName())) {
        std::cerr << "Account with the same name already exists." << std::endl;
        return;
    }

    std::vector<std::string> columns = {"name", "balance"};
    std::vector<std::string> values = {account.getName(), std::to_string(account.getBalance())};

    insertRecord("Account", columns, values);
}

void createTransaction(const std::string &type, int accountID, int categoryId,
                       const Transaction &transaction) {
    std::vector<std::string> columns = {"type", "amount", "description", "category_id", "account_id", "date"};
    std::vector<std::string> values = {type, std::to_string(transaction.getAmount()), transaction.getDescription(),
                                       (categoryId != 0) ? std::to_string(categoryId) : "NULL",
                                       std::to_string(accountID), transaction.getDate()};

    insertRecord("'Transaction'", columns, values);

    if (type == "Income") {
        std::cout << "Income was added." << std::endl;
        updateAccount(accountID, "", 0, transaction.getAmount());
    } else {
        std::cout << "Expense was added." << std::endl;

        if (categoryId != 0) {
            double budget = 0;
            std::string name{};
            updateCategory(categoryId, name, budget);
        }

        double balance = 0;
        std::string name{};

        updateAccount(accountID, name, balance, transaction.getAmount());
    }
}


///UPDATE
void updateCategory(int id, const std::string &name, double budget) {
    if (!name.empty()) {
        StatementPtr nameQuery(new SQLite::Statement(*db, "UPDATE Category SET name = ? WHERE id = ?"));
        nameQuery->bind(1, name);
        nameQuery->bind(2, id);
        if (nameQuery->exec())
            std::cout << "Edited category with id '" << id << "'. (name)" << std::endl;
        else
            std::cerr << "Editing category with id '" << id << "' unsuccessful.(name)" << std::endl;
    }

    if (budget != 0.0) {
        StatementPtr updateQuery(
                new SQLite::Statement(*db, "UPDATE Category SET budget = ?, budgetSet = 1 WHERE id = ?"));
        updateQuery->bind(1, budget);
        updateQuery->bind(2, id);
        if (updateQuery->exec())
            std::cout << "Edited category with id '" << id << "'. (budget)" << std::endl;
        else
            std::cerr << "Editing category with id '" << id << "' unsuccessful.(budget)" << std::endl;
    }

    StatementPtr checkQuery(
            new SQLite::Statement(*db, "SELECT SUM(amount) FROM `Transaction` WHERE category_id = ?"));
    StatementPtr budgetQuery(new SQLite::Statement(*db, "SELECT budget FROM Category WHERE id = ?"));

    checkQuery->bind(1, id);
    budgetQuery->bind(1, id);
    checkQuery->executeStep();
    budgetQuery->executeStep();

    double sum = checkQuery->getColumn(0).getDouble();
    double budgetAmount = budgetQuery->getColumn(0).getDouble();

    if (sum < budgetAmount)
        std::cout << "Remaining category's budget is '" << budgetAmount - sum << "' dollars." << std::endl;
    else
        std::cerr << "Category exceeded the budget by '" << sum - budgetAmount << "' dollars." << std::endl;
}

void updateAccount(int id, const std::string &name, double balance, double moneyChange) {
    if (!name.empty()) {
        StatementPtr nameQuery(new SQLite::Statement(*db, updateQuery("Account", "name")));
        nameQuery->bind(1, name);
        nameQuery->bind(2, id);

        if (nameQuery->exec())
            std::cout << "Edited account with id '" << id << "'. (name)" << std::endl;
        else
            std::cerr << "Editing account with id '" << id << "' unsuccessful.(name)" << std::endl;
    }

    if (balance != 0.0) {
        StatementPtr balanceQuery(new SQLite::Statement(*db, updateQuery("Account", "balance")));
        balanceQuery->bind(1, balance);
        balanceQuery->bind(2, id);

        if (balanceQuery->exec())
            std::cout << "Edited account with id '" << id << "'. (balance)" << std::endl;
        else
            std::cerr << "Editing account with id '" << id << "' unsuccessful.(balance)" << std::endl;
    }

    StatementPtr budgetQuery(new SQLite::Statement(*db, "SELECT balance FROM Account WHERE id = ?"));

    budgetQuery->bind(1, id);
    budgetQuery->executeStep();

    double balanceAmount = budgetQuery->getColumn(0).getDouble();

    if (moneyChange != 0.0) {
        StatementPtr changeQuery(new SQLite::Statement(*db, updateQuery("Account", "balance")));
        changeQuery->bind(1, (balanceAmount + moneyChange));
        changeQuery->bind(2, id);

        if (changeQuery->exec())
            std::cout << "Edited account with id '" << id << "'. (balance)" << std::endl;
        else
            std::cerr << "Editing account with id '" << id << "' unsuccessful.(balance)" << std::endl;
    }

    if ((balanceAmount + moneyChange) < 0)
        std::cerr << "You're out of money man..." << std::endl;
}

void
updateTransaction(int id, int accountID, int categoryId, double amount, const std::string &description,
                  const std::string &date) {
    std::vector<std::tuple<std::string, std::string, std::string>> updates;

    if (accountID != 0)
        updates.emplace_back("account_id", std::to_string(accountID), "(account_id)");
    if (categoryId != 0)
        updates.emplace_back("category_id", std::to_string(categoryId), "(category_id)");
    if (amount != 0.0)
        updates.emplace_back("amount", std::to_string(amount), "(amount)");
    if (!description.empty())
        updates.emplace_back("description", description, "(description)");
    if (!date.empty())
        updates.emplace_back("date", date, "(date)");

    for (const auto &update: updates) {
        const std::string &column = std::get<0>(update);
        const std::string &value = std::get<1>(update);
        const std::string &message = std::get<2>(update);

        StatementPtr query(new SQLite::Statement(*db, updateQuery("'Transaction'", column)));

        query->bind(1, value);
        query->bind(2, id);

        if (query->exec())
            std::cout << "Edited transaction with id '" << id << "'. " << message << std::endl;
        else
            std::cerr << "Editing transaction with id '" << id << "' unsuccessful. " << message << std::endl;
    }
}

///READ
//Funkce načítání filtrovaných transakcí:
//Funkce načítání dostupných účtů a kategorií:
//Funkce načítání typů transakcí:
//Funkce načítání dat o transakcích na základě ID:


///DELETE
void destroyEntity(const std::string &table, int id) {
    std::string queryStr = "DELETE FROM " + table + " WHERE id = ?";
    StatementPtr query(new SQLite::Statement(*db, queryStr.c_str()));
    query->bind(1, id);

    if (query->exec())
        std::cout << table << " with ID '" << id << "' deleted successfully." << std::endl;
    else
        std::cerr << table << " ID '" << id << "' not found." << std::endl;
}