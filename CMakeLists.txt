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

# Include directories for your library
#target_include_directories(lib PUBLIC
#        ${CMAKE_CURRENT_SOURCE_DIR}/lib/include
#        ${CMAKE_CURRENT_SOURCE_DIR}/lib/deps/SQLiteCpp/include
#)

# Link SQLiteCpp library to your library
target_link_libraries(lib PUBLIC SQLiteCpp sqlite3 pthread dl)

## Add directory with database files to the build directory
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lib/db DESTINATION ${CMAKE_BINARY_DIR})

# Define the main executable
add_executable(main lib/src/main.cpp)

# Link the main executable with the library
target_link_libraries(main PRIVATE lib)
