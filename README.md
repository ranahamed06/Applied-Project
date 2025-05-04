# CSCE221101 Applied Data Structures - Term Project

# Sudoku Solver

# Overview

This project is a Sudoku Game implementation in C++. The objective of the project is to build a fully functional Sudoku game that allows users to play, interact with, and solve Sudoku puzzles. The project uses object-oriented programming principles to manage the game logic, board state, and user interactions.

# Features

Sudoku Puzzle Generation: The game supports different difficulty levels (Easy, Medium, and Hard) for puzzle generation.
User Interaction: Players can place numbers, view possible candidates for a cell, undo moves, and get hints.
Game Time Tracking: The game tracks how much time the player has spent solving the puzzle.
Help & Instructions: In-game help is available to guide players on how to interact with the game.
Undo Functionality: Players can undo their last move to correct mistakes.
Game Restarts: The game can be restarted or quit at any time.

# Installation

# Prerequisites
C++ Compiler (e.g., GCC, Clang)
CMake for building the project (if using a CMake setup)
Xcode or other IDE with C++ support (optional but recommended for ease of use)

# Steps to Build and Run
1. Clone the repository.
2. Create a build directory.
3. Run CMake to configure the build.
4. Build the project.
5. Run the game.

# Usage

After running the game, players are presented with the Sudoku board and a menu of actions. The following commands can be used during the game:
p: Place a number on the board.
c: Show candidates for a selected cell.
h: Get a hint for an empty cell.
u: Undo the last move.
s: Solve the puzzle automatically.
r: Restart the game.
q: Quit the game.
?: Show the help menu with instructions.

# Project Structure

The project consists of the following files:
main.cpp: The main entry point for the application. It initializes and runs the game.
SudokuGame.h / SudokuGame.cpp: The header and source files for the SudokuGame class, which handles game logic, user input, and interactions.
SudokuBoard.h / SudokuBoard.cpp: These files define and implement the SudokuBoard class, which manages the Sudoku grid, validation, and puzzle generation.
Cell.h / Cell.cpp: Defines the Cell class, which represents each cell in the Sudoku grid and contains properties like its value and state (fixed or empty).
CustomVector.h: A custom vector implementation used for storing candidates for each empty cell.
TreeNode.h: Defines the TreeNode class, which is used for managing the decision tree during the puzzle-solving process (if relevant to the game logic).

# Contributions

This project was developed by:
Dalia Hassan - 900235756
Malak Abdelhalim - 900222407
Menna Essam - 900223396
Rana Hamed - 900225871
Youssef Aglan - 900222720
