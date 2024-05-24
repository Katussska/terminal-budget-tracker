cmake_minimum_required(VERSION 3.27)
project(Coinshen)

set(CMAKE_CXX_STANDARD 17)

# Add SQLiteCpp library
add_subdirectory(lib/deps/SQLiteCpp)

file(GLOB LIB_SRC lib/db/*.cpp lib/db/*.h lib/include/*.h lib/src/BudgetTracker.cpp)

# Add your library
add_library(lib STATIC ${LIB_SRC}
        lib/include/CommandProcessor.h
        lib/src/CommandProcessor.cpp)

# Link SQLiteCpp library to your library
target_link_libraries(lib PUBLIC SQLiteCpp sqlite3 pthread dl)

# Define the main executable
add_executable(main lib/src/main.cpp)

# Link the main executable with the library
target_link_libraries(main PRIVATE lib)
