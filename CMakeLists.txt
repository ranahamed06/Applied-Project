cmake_minimum_required(VERSION 3.30)
project(Applied_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Applied_Project
    BacktrackTree.cpp
    BacktrackTree.h
    main.cpp
    SudokuBoard.cpp
    SudokuBoard.h
    SudokuGame.cpp
    SudokuGame.h

        myvector.h)
