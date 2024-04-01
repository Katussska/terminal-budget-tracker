cmake_minimum_required(VERSION 3.27)
project(Coinshen)

set(CMAKE_CXX_STANDARD 17)

# Add SQLiteCpp library
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/deps/SQLiteCpp)

# Add your library dopsat vsevhny .cpp
add_library(lib STATIC src/BudgetTracker.cpp)

# Include directories for your library
target_include_directories(lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/LIB/include
)

# Link SQLiteCpp library to your library
target_link_libraries(lib PUBLIC SQLiteCpp sqlite3 pthread dl)

add_executable(main src/main.cpp)

target_link_libraries(main lib)