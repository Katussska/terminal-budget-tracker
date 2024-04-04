## Getting Started

To run the Budget Tracker application, follow these steps:

1. Clone the repository to your local machine.
2. Ensure you have SQLiteCpp installed. You can find installation
   instructions [here](https://github.com/SRombauts/SQLiteCpp).
3. Load CMake and run 'main'.

## Implemented Features

- **CRUD Operations**: The application supports basic CRUD (Create, Read, Update, Delete) operations for transactions,
  budget categories, and accounts. (for now no Read)
- **Transaction Management**: Users can add, edit, and delete transactions, specifying the type (income or expense),
  amount, description, date, and associated account or category.
- **Category Management**: Users can create, edit, and delete budget categories, setting a budget limit for each
  category.
- **Account Management**: Users can add, edit, and delete accounts, specifying the account name and initial balance.
- **Schema Initialization**: The application initializes the SQLite database schema using a SQL file located
  at `lib/db/schema.sql`.

## Known Limitations

- **Error Handling**: The error handling mechanism could be improved for better user feedback and error reporting. (will
  be handled more with Qt)
- **Input Validation**: The application currently lacks robust input validation, which could lead to unexpected behavior
  if invalid data is provided.
- **Yuck IDs**: The manipulation with functions sucks, but the IDs will be forwarded from Qt.

## Usage Examples

```cpp
int main() {
    // Initialize the database schema
    createSchema();

    // Add an account
    addAccount("mBank", 10000);

    // Delete existing categories
    deleteCategory(1);
    deleteCategory(2);

    // Add budget categories
    addCategory("fun", 1000);
    addCategory("gas");

    // Add transactions
    addTransaction("income", 1, 5000, "paycheck", "20.03.2024");
    addTransaction("expense", 1, 4, -1000, "20.03.2024");

    return 0;
}