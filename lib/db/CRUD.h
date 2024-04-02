//
// Created by katussska on 4/2/24.
//

#ifndef PROJECT_CRUD_H
#define PROJECT_CRUD_H

#include "../include/Transaction.h"

// todo: put this in the db class probably
inline SQLite::Database db("../lib/db/database.db", SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);

void createSchema();

void createCategory(const Category &category);

#endif //PROJECT_CRUD_H
