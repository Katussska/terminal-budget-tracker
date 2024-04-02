-- Seed for Category table
INSERT INTO Category (name, budget, budgetSet)
VALUES ('Food', 200.0, 1),
       ('Utilities', 100.0, 1),
       ('Entertainment', NULL, 0),
       ('Transportation', NULL, 0);

-- Seed for Account table
INSERT INTO Account (name, balance)
VALUES ('Savings', 1500.0),
       ('Checking', 500.0),
       ('Credit Card', 300.0);

-- Seed for Transaction table
INSERT INTO "Transaction" (type, amount, description, category_id, account_id, date)
VALUES ('expense', 50.0, 'Groceries', 1, 2, '2024-03-25 08:00:00'),
       ('income', 200.0, 'Paycheck', NULL, 2, '2024-03-15 12:00:00'),
       ('expense', 20.0, 'Dinner', 3, 2, '2024-03-20 19:30:00'),
       ('expense', 30.0, 'Gas', 4, 2, '2024-03-22 10:15:00');
