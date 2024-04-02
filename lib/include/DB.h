//
// Created by katussska on 4/2/24.
//

#ifndef COINSHEN_DB_H
#define COINSHEN_DB_H

#include <SQLiteCpp/SQLiteCpp.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <utility>
#include <sqlite3.h>
#include <ctime>

class DB {
private:
    static DB *instance;
    SQLite::Database db;

    DB() : db("../lib/db/database.db", SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE) {
        createSchema();
    }

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

public:
    static DB *getInstance() {
        if (!instance)
            instance = new DB();

        return instance;
    }

    SQLite::Database &getConnection() {
        return db;
    }
};

DB *DB::instance = nullptr;


#endif //COINSHEN_DB_H