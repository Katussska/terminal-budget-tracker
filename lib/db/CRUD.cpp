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
        throw std::invalid_argument("Columns and values must have the same size and cannot be empty.\n");

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
        std::cout << "Record inserted successfully into table '" << tableName << "'.\n" << std::endl;
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
        throw std::runtime_error("Error opening schema file\n");
    }

    std::string schemaSql((std::istreambuf_iterator<char>(schemaFile)),
                          std::istreambuf_iterator<char>());

    try {
        db->exec(schemaSql);
        std::cout << "Schema created successfully.\n" << std::endl;
    } catch (SQLite::Exception &e) {
        std::cerr << "Error executing SQL commands: " << e.what() << std::endl;
        throw std::runtime_error("Error executing SQL commands"
        );
    }
}

void createCategory(const Category &category) {
    if (recordExists("Category", category.getName())) {
        std::cerr << "Category with the same name already exists.\n" << std::endl;
        return;
    }

    std::vector<std::string> columns = {"name", "budget", "budgetSet"};
    std::vector<std::string> values = {category.getName(), std::to_string(category.getBudget()),
                                       std::to_string(category.isBudgetSet())};

    insertRecord("Category", columns, values);
}

void createAccount(const Account &account) {
    if (recordExists("Account", account.getName())) {
        std::cerr << "Account with the same name already exists.\n" << std::endl;
        return;
    }

    std::vector<std::string> columns = {"name", "balance"};
    std::vector<std::string> values = {account.getName(), std::to_string(account.getBalance())};

    insertRecord("Account", columns, values);
}

void createTransaction(const std::string &type, int accountID, int categoryId,
                       const Transaction &transaction) {
    std::vector<std::string> columns = {"type", "amount", "description", "category_id", "account_id", "date"};
    double amount = transaction.getAmount();
    if (type == "expense") {
        amount = -amount;
    }
    std::vector<std::string> values = {type, std::to_string(amount), transaction.getDescription(),
                                       (categoryId != 0) ? std::to_string(categoryId) : "NULL",
                                       std::to_string(accountID), transaction.getDate()};

    insertRecord("'Transaction'", columns, values);

    if (type == "Income") {
        std::cout << "Income was added.\n" << std::endl;
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

        updateAccount(accountID, name, balance,
                      -transaction.getAmount());
    }
}


///UPDATE
void updateCategory(int id, const std::string &name, double budget) {
    if (!name.empty()) {
        StatementPtr nameQuery(new SQLite::Statement(*db, "UPDATE Category SET name = ? WHERE id = ?"));
        nameQuery->bind(1, name);
        nameQuery->bind(2, id);
        if (nameQuery->exec())
            std::cout << "Edited category with id '" << id << "'. (name)\n" << std::endl;
        else
            std::cerr << "Editing category with id '" << id << "' unsuccessful.(name)\n" << std::endl;
    }

    if (budget != 0.0) {
        StatementPtr updateQuery(
                new SQLite::Statement(*db, "UPDATE Category SET budget = ?, budgetSet = 1 WHERE id = ?"));
        updateQuery->bind(1, budget);
        updateQuery->bind(2, id);
        if (updateQuery->exec())
            std::cout << "Edited category with id '" << id << "'. (budget)\n" << std::endl;
        else
            std::cerr << "Editing category with id '" << id << "' unsuccessful.(budget)\n" << std::endl;
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
        std::cout << "Remaining category's budget is '" << budgetAmount - sum << "' dollars.\n" << std::endl;
    else
        std::cerr << "Category exceeded the budget by '" << sum - budgetAmount << "' dollars.\n" << std::endl;
}

void updateAccount(int id, const std::string &name, double balance, double moneyChange) {
    if (!name.empty()) {
        StatementPtr nameQuery(new SQLite::Statement(*db, updateQuery("Account", "name")));
        nameQuery->bind(1, name);
        nameQuery->bind(2, id);

        if (nameQuery->exec())
            std::cout << "Edited account with id '" << id << "'. (name)\n" << std::endl;
        else
            std::cerr << "Editing account with id '" << id << "' unsuccessful.(name)\n" << std::endl;
    }

    if (balance != 0.0) {
        StatementPtr balanceQuery(new SQLite::Statement(*db, updateQuery("Account", "balance")));
        balanceQuery->bind(1, balance);
        balanceQuery->bind(2, id);

        if (balanceQuery->exec())
            std::cout << "Edited account with id '" << id << "'. (balance)\n" << std::endl;
        else
            std::cerr << "Editing account with id '" << id << "' unsuccessful.(balance)\n" << std::endl;
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
            std::cout << "Edited account with id '" << id << "'. (balance)\n" << std::endl;
        else
            std::cerr << "Editing account with id '" << id << "' unsuccessful.(balance)\n" << std::endl;
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
            std::cout << "Edited transaction with id '" << id << "'. \n" << message << std::endl;
        else
            std::cerr << "Editing transaction with id '" << id << "' unsuccessful. \n" << message << std::endl;
    }
}

///READ
void readAllCategoriesWithExpenses() {
    std::string queryStr = "SELECT Category.id, Category.name, COALESCE(SUM(`Transaction`.amount), 0) as total_expense "
                           "FROM Category LEFT JOIN `Transaction` ON Category.id = `Transaction`.category_id "
                           "GROUP BY Category.id";
    SQLite::Statement query(*db, queryStr);

    bool found = false;
    while (query.executeStep()) {
        found = true;
        std::cout << "-------------------------\n";
        std::cout << "Category ID: " << query.getColumn("id").getInt() << "\n";
        std::cout << "Name: " << query.getColumn("name").getText() << "\n";
        std::cout << "Total Expense: " << query.getColumn("total_expense").getDouble() << "\n";
        std::cout << "-------------------------\n";
    }

    if (!found) {
        std::cerr << "No categories found in the database.\n";
    }
}

void readTransactionsByCategoryId(int id) {
    std::string queryStr = "SELECT * FROM 'Transaction' WHERE category_id = ?";
    SQLite::Statement query(*db, queryStr);
    query.bind(1, id);

    bool found = false;
    while (query.executeStep()) {
        found = true;
        std::cout << "-------------------------\n";
        std::cout << "Transaction ID: " << query.getColumn("id").getInt() << "\n";
        std::cout << "Type: " << query.getColumn("type").getText() << "\n";
        std::cout << "Amount: " << query.getColumn("amount").getDouble() << "\n";
        std::cout << "Description: " << query.getColumn("description").getText() << "\n";
        std::cout << "Category ID: " << query.getColumn("category_id").getInt() << "\n";
        std::cout << "Account ID: " << query.getColumn("account_id").getInt() << "\n";
        std::cout << "Date: " << query.getColumn("date").getText() << "\n";
        std::cout << "-------------------------\n";
    }

    if (!found) {
        std::cerr << "No transactions found for category ID " << id << "\n";
    }
}

void readTransactionsByCategoryName(const std::string &name) {
    std::string queryStr = "SELECT Transaction.* FROM 'Transaction' "
                           "JOIN Category ON Transaction.category_id = Category.id "
                           "WHERE Category.name = ?";
    SQLite::Statement query(*db, queryStr);
    query.bind(1, name);

    bool found = false;
    while (query.executeStep()) {
        found = true;
        std::cout << "-------------------------\n";
        std::cout << "Transaction ID: " << query.getColumn("id").getInt() << "\n";
        std::cout << "Type: " << query.getColumn("type").getText() << "\n";
        std::cout << "Amount: " << query.getColumn("amount").getDouble() << "\n";
        std::cout << "Description: " << query.getColumn("description").getText() << "\n";
        std::cout << "Category ID: " << query.getColumn("category_id").getInt() << "\n";
        std::cout << "Account ID: " << query.getColumn("account_id").getInt() << "\n";
        std::cout << "Date: " << query.getColumn("date").getText() << "\n";
        std::cout << "-------------------------\n";
    }

    if (!found) {
        std::cerr << "No transactions found for category name " << name << "\n";
    }
}

void readAllAccountsWithBalance() {
    std::string queryStr = "SELECT id, name, balance FROM Account";
    SQLite::Statement query(*db, queryStr);

    while (query.executeStep()) {
        std::cout << "-------------------------\n";
        std::cout << "Account ID: " << query.getColumn("id").getInt() << "\n";
        std::cout << "Name: " << query.getColumn("name").getText() << "\n";
        std::cout << "Balance: " << query.getColumn("balance").getDouble() << "\n";
        std::cout << "-------------------------\n";
    }
}

void readAccountDetailsById(int id) {
    std::string queryStr = "SELECT * FROM Account WHERE id = ?";
    SQLite::Statement query(*db, queryStr);
    query.bind(1, id);

    if (query.executeStep()) {
        std::cout << "-------------------------\n";
        std::cout << "Account ID: " << query.getColumn("id").getInt() << "\n";
        std::cout << "Name: " << query.getColumn("name").getText() << "\n";
        std::cout << "Balance: " << query.getColumn("balance").getDouble() << "\n";
    } else {
        std::cerr << "No account found with ID " << id << "\n";
        return;
    }

    queryStr = "SELECT * FROM 'Transaction' WHERE account_id = ?";
    SQLite::Statement transactionQuery(*db, queryStr);
    transactionQuery.bind(1, id);

    while (transactionQuery.executeStep()) {
        std::cout << "-------------------------\n";
        std::cout << "Transaction ID: " << transactionQuery.getColumn("id").getInt() << "\n";
        std::cout << "Type: " << transactionQuery.getColumn("type").getText() << "\n";
        std::cout << "Amount: " << transactionQuery.getColumn("amount").getDouble() << "\n";
        std::cout << "Description: " << transactionQuery.getColumn("description").getText() << "\n";
        std::cout << "Category ID: " << transactionQuery.getColumn("category_id").getInt() << "\n";
        std::cout << "Account ID: " << transactionQuery.getColumn("account_id").getInt() << "\n";
        std::cout << "Date: " << transactionQuery.getColumn("date").getText() << "\n";
        std::cout << "-------------------------\n";
    }
}

void readAccountDetailsByName(const std::string &name) {
    std::string queryStr = "SELECT * FROM Account WHERE name = ?";
    SQLite::Statement query(*db, queryStr);
    query.bind(1, name);

    if (query.executeStep()) {
        std::cout << "-------------------------\n";
        std::cout << "Account ID: " << query.getColumn("id").getInt() << "\n";
        std::cout << "Name: " << query.getColumn("name").getText() << "\n";
        std::cout << "Balance: " << query.getColumn("balance").getDouble() << "\n";
    } else {
        std::cerr << "No account found with name " << name << "\n";
        return;
    }

    int accountId = query.getColumn("id").getInt();

    queryStr = "SELECT * FROM 'Transaction' WHERE account_id = ?";
    SQLite::Statement transactionQuery(*db, queryStr);
    transactionQuery.bind(1, accountId);

    while (transactionQuery.executeStep()) {
        std::cout << "-------------------------\n";
        std::cout << "Transaction ID: " << transactionQuery.getColumn("id").getInt() << "\n";
        std::cout << "Type: " << transactionQuery.getColumn("type").getText() << "\n";
        std::cout << "Amount: " << transactionQuery.getColumn("amount").getDouble() << "\n";
        std::cout << "Description: " << transactionQuery.getColumn("description").getText() << "\n";
        std::cout << "Category ID: " << transactionQuery.getColumn("category_id").getInt() << "\n";
        std::cout << "Account ID: " << transactionQuery.getColumn("account_id").getInt() << "\n";
        std::cout << "Date: " << transactionQuery.getColumn("date").getText() << "\n";
        std::cout << "-------------------------\n";
    }
}

void readTransactionsByType(const std::string &type) {
    std::string queryStr;
    if (type == "all") {
        queryStr = "SELECT * FROM 'Transaction'";
    } else {
        queryStr = "SELECT * FROM 'Transaction' WHERE type = ?";
    }

    SQLite::Statement query(*db, queryStr);

    if (type != "all") {
        query.bind(1, type);
    }

    bool found = false;
    while (query.executeStep()) {
        found = true;
        std::cout << "-------------------------\n";
        std::cout << "Transaction ID: " << query.getColumn("id").getInt() << "\n";
        std::cout << "Type: " << query.getColumn("type").getText() << "\n";
        std::cout << "Amount: " << query.getColumn("amount").getDouble() << "\n";
        std::cout << "Description: " << query.getColumn("description").getText() << "\n";
        std::cout << "Category ID: " << query.getColumn("category_id").getInt() << "\n";
        std::cout << "Account ID: " << query.getColumn("account_id").getInt() << "\n";
        std::cout << "Date: " << query.getColumn("date").getText() << "\n";
        std::cout << "-------------------------\n";
    }

    if (!found) {
        std::cerr << "No transactions found\n";
    }
}

///DELETE
void destroyAccount(int id) {
    std::string queryStr = "SELECT * FROM 'Transaction' WHERE account_id = ?";
    SQLite::Statement query(*db, queryStr);
    query.bind(1, id);

    while (query.executeStep()) {
        int categoryId = query.getColumn("category_id").getInt();
        double amount = query.getColumn("amount").getDouble();

        if (categoryId != 0) {
            std::string categoryQueryStr = "SELECT budget, budgetSet FROM Category WHERE id = ?";
            SQLite::Statement categoryQuery(*db, categoryQueryStr);
            categoryQuery.bind(1, categoryId);

            if (categoryQuery.executeStep()) {
                double currentBudget = categoryQuery.getColumn("budget").getDouble();
                int budgetSet = categoryQuery.getColumn("budgetSet").getInt();

                if (budgetSet == 1) {
                    std::string updateQueryStr = "UPDATE Category SET budget = ? WHERE id = ?";
                    SQLite::Statement updateQuery(*db, updateQueryStr);
                    updateQuery.bind(1, currentBudget + amount);
                    updateQuery.bind(2, categoryId);
                    updateQuery.exec();
                }
            }
        }

        std::string deleteQueryStr = "DELETE FROM 'Transaction' WHERE id = ?";
        SQLite::Statement deleteQuery(*db, deleteQueryStr);
        deleteQuery.bind(1, query.getColumn("id").getInt());
        deleteQuery.exec();
    }

    std::string deleteAccountQueryStr = "DELETE FROM Account WHERE id = ?";
    SQLite::Statement deleteAccountQuery(*db, deleteAccountQueryStr);
    deleteAccountQuery.bind(1, id);
    deleteAccountQuery.exec();
}

void destroyTransaction(int id) {
    std::string queryStr = "SELECT * FROM 'Transaction' WHERE id = ?";
    SQLite::Statement query(*db, queryStr);
    query.bind(1, id);

    if (query.executeStep()) {
        int accountId = query.getColumn("account_id").getInt();
        int categoryId = query.getColumn("category_id").getInt();
        double amount = query.getColumn("amount").getDouble();

        std::string accountQueryStr = "SELECT balance FROM Account WHERE id = ?";
        SQLite::Statement accountQuery(*db, accountQueryStr);
        accountQuery.bind(1, accountId);

        if (accountQuery.executeStep()) {
            double currentBalance = accountQuery.getColumn("balance").getDouble();
            std::string updateAccountQueryStr = "UPDATE Account SET balance = ? WHERE id = ?";
            SQLite::Statement updateAccountQuery(*db, updateAccountQueryStr);
            updateAccountQuery.bind(1, currentBalance + amount);
            updateAccountQuery.bind(2, accountId);
            updateAccountQuery.exec();
        }

        if (categoryId != 0) {
            std::string categoryQueryStr = "SELECT budget, budgetSet FROM Category WHERE id = ?";
            SQLite::Statement categoryQuery(*db, categoryQueryStr);
            categoryQuery.bind(1, categoryId);

            if (categoryQuery.executeStep()) {
                double currentBudget = categoryQuery.getColumn("budget").getDouble();
                int budgetSet = categoryQuery.getColumn("budgetSet").getInt();

                if (budgetSet == 1) {
                    std::string updateCategoryQueryStr = "UPDATE Category SET budget = ? WHERE id = ?";
                    SQLite::Statement updateCategoryQuery(*db, updateCategoryQueryStr);
                    updateCategoryQuery.bind(1, currentBudget + amount);
                    updateCategoryQuery.bind(2, categoryId);
                    updateCategoryQuery.exec();
                }
            }
        }

        std::string deleteQueryStr = "DELETE FROM 'Transaction' WHERE id = ?";
        SQLite::Statement deleteQuery(*db, deleteQueryStr);
        deleteQuery.bind(1, id);
        deleteQuery.exec();
    } else {
        std::cerr << "Transaction ID '" << id << "' not found." << std::endl;
    }
}

void destroyCategory(int id) {
    std::string updateQueryStr = "UPDATE 'Transaction' SET category_id = NULL WHERE category_id = ?";
    SQLite::Statement updateQuery(*db, updateQueryStr);
    updateQuery.bind(1, id);
    updateQuery.exec();

    std::string deleteQueryStr = "DELETE FROM Category WHERE id = ?";
    SQLite::Statement deleteQuery(*db, deleteQueryStr);
    deleteQuery.bind(1, id);
    deleteQuery.exec();
}