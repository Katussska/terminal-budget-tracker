# Coinshen - Budget Tracking Console Application

Coinshen is a budget tracking console application developed as a school project. The name "Coinshen" is inspired by
Caishen, the Chinese god of wealth and prosperity. The application helps users manage their expenses, set budget goals,
and generate reports on their spending habits.

## Built With

- **C++:** The application's logic and necessary functionalities are implemented in C++.
- **SQLite:** Coinshen uses SQLite as its embedded database to store all records of accounts, categories, and
  transactions.

## Features

- **Expense Tracking:** Users can input their expenses along with relevant details such as category, amount,
  description, and date. The application organizes and stores this data for further analysis.

- **Budget Setting:** Users can set budget goals for different expense categories (e.g., groceries, utilities,
  entertainment). The application provides alerts when users exceed their set budget limits.

- **Category Management:** Users can create, and delete expense categories according to their preferences and
  needs.

## Building and Running the Application

This project uses CMake as its build system. To build and run the application, follow these steps:

1. **Clone the repository:**

   First, clone the repository to your local machine:

    ```bash
    git clone git@github.com:Katussska/Coinshen.git
    ```

2. **Navigate to the project directory:**

   Change your current directory to the project's directory:

    ```bash
    cd Coinshen
    ```

3. **Clone the SQLiteCpp repository:**

   Navigate to the `lib/deps` directory and clone the SQLiteCpp repository:

    ```bash
    cd lib
    mkdir deps
    cd deps
    git clone git@github.com:SRombauts/SQLiteCpp.git
    ```

4. **Return to the project root directory:**

   Navigate back to the project root directory:

    ```bash
    cd ../..
    ```

5. **Create a build directory:**

   Create a new directory named `build`:

    ```bash
    mkdir build
    ```

6. **Navigate to the build directory:**

   Change your current directory to the `build` directory:

    ```bash
   cd build
    ```

7. **Run CMake:**

   Run the `cmake` command to generate the Makefile:

    ```bash
    cmake ..
    ```

8. **Build the project:**

   Build the project using the `make` command:

    ```bash
    make
    ```

9. **Run the application:**

   After successfully building the project, you can run the application:

    ```bash
    ./main
    ```

## License

This project is licensed under the MIT License.
