#include "SudokuBoard.h"
using namespace std;

// Constructor to initialize the board with some initial values (you can change this later)
SudokuBoard::SudokuBoard() {
    int initialBoard[SIZE][SIZE] = {
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

    // Initialize the board with the initial values
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = initialBoard[i][j];
        }
    }
}

// Display the current board
void SudokuBoard::printBoard() {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            cout << board[r][c] << " ";
            if (c == 2 || c == 5) cout << "| ";  // Add vertical separator
        }
        cout << endl;

        if (r == 2 || r == 5) cout << "---------------------" << endl;  // Add horizontal separator
    }
}

void SudokuBoard::setCell(int row, int col, int value) {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
        board[row][col] = value;  // Set the value of the cell
    }
}

// Validate if a move is legal (row, column, subgrid)
bool SudokuBoard::isValidMove(int row, int col, int num) {
    // Check if the number exists in the row
    for (int c = 0; c < SIZE; c++) {
        if (board[row][c] == num) return false;
    }

    // Check if the number exists in the column
    for (int r = 0; r < SIZE; r++) {
        if (board[r][col] == num) return false;
    }

    // Check the 3x3 subgrid
    int boxRowStart = (row / 3) * 3;
    int boxColStart = (col / 3) * 3;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (board[boxRowStart + r][boxColStart + c] == num) return false;
        }
    }

    return true;
}

bool SudokuBoard::findEmptyCell(int &row, int &col) {
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) {
                return true;  // Found an empty cell
            }
        }
    }
    return false;  // No empty cells, board is complete
}

bool SudokuBoard::solveSudoku() {
    int row, col;
    
    // Step 1: Find the next empty cell
    if (!findEmptyCell(row, col)) {
        // No empty cells, the board is solved!
        return true;
    }

    // Step 2: Try numbers 1-9 in the empty cell
    for (int num = 1; num <= 9; num++) {
        // Step 3: Check if placing num in (row, col) is valid
        if (isValidMove(row, col, num)) {
            // Place the number
            board[row][col] = num;

            // Recurse to solve the rest of the board
            if (solveSudoku()) {
                return true;  // If the board is solved, return true
            }

            // Step 4: Backtrack if no solution is found
            board[row][col] = 0;  // Reset the cell
        }
    }

    // If no number 1-9 is valid, return false to backtrack
    return false;
}


// Check if the board is complete (i.e., no empty cells)
bool SudokuBoard::isComplete() {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (board[r][c] == 0) return false;  // If there's any empty cell
        }
    }
    return true;
}

// Place a number in a given cell
void SudokuBoard::makeMove(int row, int col, int num) {
    board[row][col] = num;
}

// Function to get the value of a specific cell (row, col)
int SudokuBoard::getCell(int row, int col) const {
    // Ensure that the row and column are within bounds
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
        return board[row][col];
    } else {
        // Return -1 or some other error code if the row/col is out of bounds
        cout << "Invalid row or column" << endl;
        return -1;
    }
}

// Function to generate a solved Sudoku grid using backtracking
bool SudokuBoard::generateSolvedBoard() {
    // Start with an empty board (all cells are 0)
    clearBoard(); // Make sure the board is empty before generating

    // Solve the Sudoku puzzle using backtracking
    return solveSudoku();
}

// Function to clear the board
void SudokuBoard::clearBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0; // Clear each cell
        }
    }
}

