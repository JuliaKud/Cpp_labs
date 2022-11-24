cmake_minimum_required(VERSION 3.22)
project(lab05_tic_tac_toe)

set(CMAKE_CXX_STANDARD 14)

include_directories(solution/include)

add_executable(lab05_tic_tac_toe
        solution/include/game.h
        solution/include/view.h
        solution/src/game.cpp
        solution/src/main.cpp
        solution/src/view_compact.cpp
        solution/src/view_pretty.cpp)
