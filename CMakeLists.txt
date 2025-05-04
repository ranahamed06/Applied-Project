cmake_minimum_required(VERSION 3.30)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        untitled
        main.cpp
        Cell.cpp
        Cell.h
        CustomVector.h
        SudokuGame.cpp
        SudokuBoard.cpp
        SudokuBoard.h
        SudokuGame.h
        TreeNode.h)
