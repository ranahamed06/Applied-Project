#include "SudokuGame.h"
#include "SudokuBoard.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void SudokuGame::startGame() {
    int row, col, num;

    // Main game loop
    while (!board.isComplete()) {
        // Display the current board
        board.printBoard();

        // Ask the user whether they want to solve the puzzle automatically
        cout << "Would you like to solve the puzzle? (y/n): ";
        char choice;
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            // Call the backtracking solver to solve the puzzle
            if (board.solveSudoku()) {
                autoSolve();  // Show the solved board
                break;
            } else {
                cout << "No solution exists for the given puzzle." << endl;
            }
        } else {
            cout << "Continuing with the game, feel free to solve manually!" << endl;
        }

        // Prompt the user for input
        cout << "Enter row (1-9), column (1-9), and number (1-9): ";
        cin >> row >> col >> num;

        // Convert user input from 1-indexed to 0-indexed
        row--;  
        col--;

        // Validate the move
        if (board.isValidMove(row, col, num)) {
            // Make the move
            board.makeMove(row, col, num);
        } else {
            cout << "Invalid move! Try again." << endl;
        }
    }
    

    // Game is complete!
    cout << "Game over!" << endl;
}

void SudokuGame::initializePuzzle() {
    // Load or generate a puzzle and set it on the board
    // Example puzzle, can be replaced with a random generator or user input
    int puzzle[SIZE][SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    // Set the puzzle on the board
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            board.setCell(row, col, puzzle[row][col]);
        }
    }
}

void SudokuGame::autoSolve() {
    if (board.solveSudoku()) {
        cout << "Sudoku puzzle solved!" << endl;
        board.printBoard();  // Show the solved board
    } else {
        cout << "No solution exists for the given puzzle." << endl;
    }
}

// Function to generate a new random puzzle
void SudokuGame::generateRandomPuzzle(int difficulty) {
    // Generate a completely solved board first
    board.generateSolvedBoard();

    // Based on the difficulty level, remove numbers from the board
    int cellsToRemove = 0;

    if (difficulty == 1) {
        cellsToRemove = 40; // Easy: Remove 40 cells
    } else if (difficulty == 2) {
        cellsToRemove = 50; // Medium: Remove 50 cells
    } else if (difficulty == 3) {
        cellsToRemove = 60; // Hard: Remove 60 cells
    }

    srand(time(0)); // Seed the random number generator

    // Remove the numbers randomly
    for (int i = 0; i < cellsToRemove; i++) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;

        // Keep removing until we find a cell that isn't already empty
        while (board.getCell(row, col) == 0) {
            row = rand() % SIZE;
            col = rand() % SIZE;
        }

        // Set the cell to 0 to remove the number
        board.setCell(row, col, 0);
    }
}