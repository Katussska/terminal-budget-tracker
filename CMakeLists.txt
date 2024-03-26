cmake_minimum_required(VERSION 3.27)
project(project)

set(CMAKE_CXX_STANDARD 17)

add_executable(project src/main.cpp
        src/Transaction.cpp
        include/Transaction.h
        src/FinancialEntity.cpp
        include/FinancialEntity.h
        src/BudgetTracker.cpp
        include/BudgetTracker.h)
