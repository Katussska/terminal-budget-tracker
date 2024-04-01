CREATE TABLE IF NOT EXISTS Category (
    id        INTEGER PRIMARY KEY AUTOINCREMENT,
    name      TEXT NOT NULL,
    budget    REAL ,
    budgetSet INTEGER NOT NULL DEFAULT 0
);

CREATE TABLE IF NOT EXISTS Account (
    id      INTEGER PRIMARY KEY AUTOINCREMENT,
    name    TEXT NOT NULL,
    balance REAL NOT NULL
);

CREATE TABLE IF NOT EXISTS "Transaction" (
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    type        TEXT CHECK ( type in ('expense', 'income') ) NOT NULL,
    amount      REAL NOT NULL,
    description TEXT,
    category_id INTEGER,
    account_id     INTEGER,
    date        TIMESTAMP NOT NULL,
    FOREIGN KEY (category_id) REFERENCES Category (id),
    FOREIGN KEY (account_id) REFERENCES Account (id)
    );
