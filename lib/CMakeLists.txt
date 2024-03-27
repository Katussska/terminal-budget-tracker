cmake_minimum_required(VERSION 3.27)
project(Coinshen)

set(CMAKE_CXX_STANDARD 17)

# Add SQLiteCpp library
add_subdirectory(SQLiteCpp)

# Add your library
add_library(lib STATIC src/BudgetTracker.cpp)

# Include directories for your library
target_include_directories(lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/LIB/include
)

# Link SQLiteCpp library to your library
target_link_libraries(lib PUBLIC SQLiteCpp sqlite3)
