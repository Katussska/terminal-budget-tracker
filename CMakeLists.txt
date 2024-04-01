cmake_minimum_required(VERSION 3.27)
project(Coinshen)

set(CMAKE_CXX_STANDARD 17)

# Add SQLiteCpp library
add_subdirectory(lib/deps/SQLiteCpp)

# Add your library
add_library(lib STATIC
        lib/src/FinancialEntity.cpp
        lib/src/Transaction.cpp
        lib/src/BudgetTracker.cpp
)

# Include directories for your library
target_include_directories(lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/include
)

# Link SQLiteCpp library to your library
target_link_libraries(lib PUBLIC SQLiteCpp sqlite3 pthread dl)

add_executable(main lib/src/main.cpp)

target_link_libraries(main PRIVATE lib)