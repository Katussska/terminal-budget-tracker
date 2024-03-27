CREATE TABLE FinancialEntity
(
    id    INTEGER PRIMARY KEY AUTOINCREMENT,
    name  TEXT NOT NULL,
    money REAL NOT NULL DEFAULT 0
);

CREATE TABLE Category
(
    id        INTEGER PRIMARY KEY AUTOINCREMENT,
    name      TEXT    NOT NULL,
    budget    REAL,
    budgetSet INTEGER NOT NULL DEFAULT 0
);

CREATE TABLE Account
(
    id      INTEGER PRIMARY KEY AUTOINCREMENT,
    name    TEXT NOT NULL,
    balance REAL NOT NULL
);

CREATE TABLE "Transaction"
(
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    account_id  INTEGER,
    amount      REAL NOT NULL,
    description TEXT,
    date        TEXT NOT NULL,
    FOREIGN KEY (account_id) REFERENCES Account (id)
);

CREATE TABLE Expense
(
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    account_id  INTEGER,
    category_id INTEGER,
    amount      REAL NOT NULL,
    description TEXT,
    date        TEXT NOT NULL,
    FOREIGN KEY (account_id) REFERENCES Account (id),
    FOREIGN KEY (category_id) REFERENCES Category (id)
);

CREATE TABLE Income
(
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    account_id  INTEGER,
    amount      REAL NOT NULL,
    description TEXT,
    date        TEXT NOT NULL,
    FOREIGN KEY (account_id) REFERENCES Account (id)
);
