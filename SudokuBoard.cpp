//
// Created by Malak Abdelhalim on 04/05/2025.
//

#include "SudokuBoard.h"
#include <iostream>
using namespace std;

// Initialize the grid
SudokuBoard::SudokuBoard() {
    clear();
}

void SudokuBoard::clear() {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            grid[row][col] = Cell();
        }
    }
}

Cell& SudokuBoard::getCell(int row, int col) {
    return grid[row][col];
}

const Cell& SudokuBoard::getCell(int row, int col) const {
    return grid[row][col];
}

void SudokuBoard::setValue(int row, int col, int value, bool fixed) {
    grid[row][col].setValue(value);
    grid[row][col].setFixed(fixed);

    // Update candidates for this cell and affected cells
    if (value != 0) {
        updateCandidates(row, col, value);
    }
}

bool SudokuBoard::isValid(int row, int col, int value) const {
    // Check if value is valid in the row
    for (int c = 0; c < SIZE; c++) {
        if (c != col && grid[row][c].getValue() == value)
          return false;
    }

    // Check if value is valid in the column
    for (int r = 0; r < SIZE; r++) {
        if (r != row && grid[r][col].getValue() == value)
          return false;
    }

    // Check if value is valid in the 3x3 box
    int boxStartRow = (row / BOX_SIZE) * BOX_SIZE;
    int boxStartCol = (col / BOX_SIZE) * BOX_SIZE;
    for (int r = boxStartRow; r < boxStartRow + BOX_SIZE; r++) {
        for (int c = boxStartCol; c < boxStartCol + BOX_SIZE; c++) {
            if ((r != row || c != col) && grid[r][c].getValue() == value)
              return false;
        }
    }

    return true;
}

bool SudokuBoard::isSolved() const {
    // Check if the board is completely filled
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (grid[row][col].getValue() == 0)
              return false;
        }
    }

    // Check if all entries are valid
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            int value = grid[row][col].getValue();

            // Temporarily set the value to 0 to check validity
            Cell temp = grid[row][col];
            const_cast<SudokuBoard*>(this)->grid[row][col].setValue(0);
            bool valid = isValid(row, col, value);
            const_cast<SudokuBoard*>(this)->grid[row][col] = temp;
            if (!valid)
              return false;
        }
    }

    return true;
}

void SudokuBoard::updateCandidates(int row, int col, int value) {
    // Remove the value from candidates in the same row
    for (int c = 0; c < SIZE; c++) {
        if (grid[row][c].isEmpty()) {
            grid[row][c].removeCandidate(value);
        }
    }

    // Remove the value from candidates in the same column
    for (int r = 0; r < SIZE; r++) {
        if (grid[r][col].isEmpty()) {
            grid[r][col].removeCandidate(value);
        }
    }

    // Remove the value from candidates in the same 3x3 box
    int boxStartRow = (row / BOX_SIZE) * BOX_SIZE;
    int boxStartCol = (col / BOX_SIZE) * BOX_SIZE;
    for (int r = boxStartRow; r < boxStartRow + BOX_SIZE; r++) {
        for (int c = boxStartCol; c < boxStartCol + BOX_SIZE; c++) {
            if (grid[r][c].isEmpty()) {
                grid[r][c].removeCandidate(value);
            }
        }
    }
}

void SudokuBoard::refreshCandidates() {
    // Reset candidates for all cells
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            grid[row][col].restoreCandidates();
        }
    }

    // Update candidates based on filled cells
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            int value = grid[row][col].getValue();
            if (value != 0) {
                updateCandidates(row, col, value);
            }
        }
    }
}
/*
bool SudokuBoard::solveRecursive(int row, int col) {

    // If we've filled the entire board, we're done
    if (row >= SIZE)
      return true;

    // Calculate next cell
    int nextRow = (col == SIZE - 1) ? row + 1 : row;
    int nextCol = (col == SIZE - 1) ? 0 : col + 1;

    // If the current cell is already filled, move to the next one
    if (grid[row][col].getValue() != 0) {
        return solveRecursive(nextRow, nextCol);
    }

    // Try each possible value (1-9) for the current cell
    for (int value = 1; value <= SIZE; value++) {
        if (isValid(row, col, value)) {
            grid[row][col].setValue(value);
            // Recursively solve for the next cell
            if (solveRecursive(nextRow, nextCol))
              return true;
            // Backtrack if the solution doesn't work
            grid[row][col].setValue(0);
        }
    }
    // No valid value found
    return false;
}

*/// Class-level variable to track recursion calls
int SudokuBoard::recursionCalls = 0;
int SudokuBoard::currentDepth = 0;
int SudokuBoard::maxRecursionDepth = 0;


//int SudokuBoard::recursionDepth = 0;
/*bool SudokuBoard::solveRecursive(int row, int col) {
    // Increment recursion depth at the start of each function call
    recursionDepth++;

    // If we've filled all rows, the puzzle is solved
    if (row == SIZE) {
        return true;
    }

    // Move to the next row if we've reached the end of the current one
    if (col == SIZE) {
        return solveRecursive(row + 1, 0);
    }

    // If the current cell is not empty, skip it (move to the next one)
    if (grid[row][col].getValue() != 0) {
        return solveRecursive(row, col + 1);  // Move to the next column
    }

    // Try placing a number 1-9 in the current empty cell
    for (int value = 1; value <= 9; value++) {
        if (isValid(row, col, value)) {
            grid[row][col].setValue(value);  // Place the number

            // Recurse to the next empty cell
            if (solveRecursive(row, col + 1)) {
                return true;
            }

            // Backtrack if placing `num` doesn't lead to a solution
            grid[row][col].setValue(0);
        }
    }

    // If no valid number can be placed, return false (backtracking)
    return false;
}*/

bool SudokuBoard::solveRecursive(int row, int col) {
    // If we reach the end of the row, move to the next row
    if (row == SIZE) {
        return true;
    }

    // If we reach the end of the column, move to the next row, first column
    if (col == SIZE) {
        return solveRecursive(row + 1, 0);
    }

    // If the current cell is already filled, skip it
    if (grid[row][col].getValue() != 0) {
        return solveRecursive(row, col + 1);
    }

    // Use Minimum Remaining Values (MRV) Heuristic
    std::pair<int, int> nextCell = findCellWithFewestChoices();
    row = nextCell.first;
    col = nextCell.second;

    // Try placing a number from 1 to 9
    for (int value = 1; value <= 9; value++) {
        if (isValid(row, col, value)) {
            grid[row][col].setValue(value);  // Place the number

            // Recurse to the next empty cell
            if (solveRecursive(row, col + 1)) {
                return true;
            }

            // Backtrack if placing `value` didn't work
            grid[row][col].setValue(0);
        }
    }

    return false;  // Backtrack if no valid number can be placed
}


/*bool SudokuBoard::solve() {
    recursionDepth = 0;
    
    
    // Call the recursive solve function starting from the top-left corner
    bool solve = solveRecursive(0, 0);

    // After the puzzle is solved, print the total recursion depth
    std::cout << "Total recursion depth: " << recursionDepth << std::endl;
    
    return solve;
}*/

std::pair<int, int> SudokuBoard::findCellWithFewestChoices() {
    int minChoices = SIZE + 1;  // More than the max possible number of choices (9)
    int bestRow = -1;
    int bestCol = -1;

    // Iterate through all cells and find the one with the fewest valid choices
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (grid[r][c].getValue() == 0) {  // Check only empty cells
                int validChoices = countValidChoices(r, c);
                if (validChoices < minChoices) {
                    minChoices = validChoices;
                    bestRow = r;
                    bestCol = c;
                }
            }
        }
    }

    return {bestRow, bestCol};
}
int SudokuBoard::countValidChoices(int row, int col) const {
    int count = 0;
    for (int value = 1; value <= 9; value++) {
        if (isValid(row, col, value)) {
            count++;
        }
    }
    return count;
}



bool SudokuBoard::solve() {
    recursionCalls = 0;
    currentDepth = 0;
    maxRecursionDepth = 0;

    bool solved = solveRecursive(0, 0);

    cout << "Total recursion calls: " << recursionCalls << endl;
    cout << "Maximum recursion depth: " << maxRecursionDepth << endl;

    return solved;
}

// Returns the number of empty cells
int SudokuBoard::getEmptyCount() const {
    int count = 0;
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (grid[row][col].getValue() == 0)
              count++;
        }
    }
    return count;
}

// Generate a complete valid Sudoku board (fully filled)
void SudokuBoard::generateCompleteBoard() {
    clear();
    solve();
}

// Remove cells to create a puzzle of the specified difficulty
void SudokuBoard::createPuzzle(int difficulty) {
    // First, generate a complete valid board
    generateCompleteBoard();

    // Then, remove cells based on difficulty
    int cellsToRemove;
    switch (difficulty) {
        case 1: // Easy
            cellsToRemove = 40; // Leaves about 41 clues
        break;
        case 2: // Medium
            cellsToRemove = 50; // Leaves about 31 clues
        break;
        case 3: // Hard
            cellsToRemove = 60; // Leaves about 21 clues
        break;
        default:
            cellsToRemove = 45;
    }

    // Make a copy of the board to test solutions
    SudokuBoard tempBoard;

    // Remember which cells have been removed
    bool removed[SIZE][SIZE] = {{false}};

    // Remove cells randomly while ensuring unique solution
    while (cellsToRemove > 0) {
        int row = std::rand() % SIZE;
        int col = std::rand() % SIZE;

        // Skip if already removed
        if (removed[row][col]) {
            continue;
        }

        // Temporarily remove the cell and check if the solution is still unique
        int temp = grid[row][col].getValue();
        grid[row][col].setValue(0);
        removed[row][col] = true;

        // Now check that the puzzle has a unique solution
        // For simplicity, we'll just check that the current removal doesn't
        // make the puzzle unsolvable

        // Copy the current board
        for (int r = 0; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                tempBoard.setValue(r, c, grid[r][c].getValue());
            }
        }

        // If the board is still solvable, keep the removal
        if (tempBoard.solve()) {
            cellsToRemove--;
        } else {
            // Restore the cell
            grid[row][col].setValue(temp);
            removed[row][col] = false;
        }
    }

    // Set all remaining cells as fixed
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (grid[row][col].getValue() != 0) {
                grid[row][col].setFixed(true);
            }
        }
    }

    // Update candidates for all cells
    refreshCandidates();
}

// Save the current state of the board to a grid for reload
void SudokuBoard::saveState(int savedGrid[SIZE][SIZE]) const {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            savedGrid[row][col] = grid[row][col].getValue();
        }
    }
}

// Load state from a saved grid
void SudokuBoard::loadState(const int savedGrid[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            grid[row][col].setValue(savedGrid[row][col]);
        }
    }

    refreshCandidates();
}


