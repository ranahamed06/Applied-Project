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

// Existing static member for recursive solver calls
int SudokuBoard::recursionDepth = 0;

// static member for tree-based solver calls/nodes
int SudokuBoard::treeNodesVisited = 0; // Initialize to 0


bool SudokuBoard::solveRecursive(int row, int col) {
    recursionDepth++;
    
    if (row == SIZE) {
        return true;
    }
    if (col == SIZE) {
        return solveRecursive(row + 1, 0);
    }
    if (grid[row][col].getValue() != 0) {
        return solveRecursive(row, col + 1);
    }
    for (int value = 1; value <= 9; value++) {
        if (isValid(row, col, value)) {
            grid[row][col].setValue(value);
            if (solveRecursive(row, col + 1)) {
                return true;
            }
            grid[row][col].setValue(0);
        }
    }
    return false;
}


bool SudokuBoard::solve() {
    recursionDepth = 0; // Reset recursion depth for each solve call
    return solveRecursive(0, 0);
}


bool SudokuBoard::solveBacktracking(TreeNode<SudokuBoard>* currentNode) {

    treeNodesVisited++; 

    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (grid[row][col].getValue() == 0) {
                for (int num = 1; num <= 9; ++num) {
                    if (isValid(row, col, num)) {
                        grid[row][col].setValue(num);

                        TreeNode<SudokuBoard>* child = new TreeNode<SudokuBoard>(*this);
                        currentNode->addChild(child);

                        if (solveBacktracking(child)) {
                            return true;
                        }

                        // Backtrack
                        grid[row][col].setValue(0);
                    }
                }
                return false; // No valid number found
            }
        }
    }
    return true; // Board filled
}


bool SudokuBoard::solve(char c) {
    if (c == 'v' || c == 'V')
    {
        recursionDepth = 0; 
        bool solved = solveRecursive(0, 0);
        std::cout << "Total number of recursion calls: " << recursionDepth << std::endl; 
        return solved;
    }
    if (c == 't' || c == 'T')
    {
        treeNodesVisited = 0; 
        TreeNode<SudokuBoard>* root = new TreeNode<SudokuBoard>(*this);
        
        treeNodesVisited = 1; 
        bool result = solveBacktracking(root);
        delete root; // prevent memory leak
        std::cout << "Total tree nodes visited: " << treeNodesVisited << std::endl; 
        return result;
    }
    return false; // invalid input
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
    clear(); // removes what the player have done
    
    solve(); // Call the non-printing internal solve()
}

// Remove cells to create a puzzle of the specified difficulty
void SudokuBoard::createPuzzle(int difficulty) {
    // First, generate a complete valid board
    generateCompleteBoard(); // This calls solve() which calls solveRecursive silently

    int cellsToRemove;
    switch (difficulty) {
        case 1: cellsToRemove = 40; break;
        case 2: cellsToRemove = 50; break;
        case 3: cellsToRemove = 60; break;
        default: cellsToRemove = 45;
    }

    bool removed[SIZE][SIZE] = {{false}};

    while (cellsToRemove > 0) {
        int row = std::rand() % SIZE;
        int col = std::rand() % SIZE;

        if (removed[row][col]) {
            continue;
        }

        int temp = grid[row][col].getValue();
        grid[row][col].setValue(0);
        removed[row][col] = true;

        SudokuBoard tempBoard;
        // Copy the current state of the board
        for (int r = 0; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                tempBoard.setValue(r, c, grid[r][c].getValue());
            }
        }

       
        if (tempBoard.solve()) { // Call the non-printing internal solve()
            cellsToRemove--;
        } else {
            // Restore the cell (undo removal)
            grid[row][col].setValue(temp);
            removed[row][col] = false;
        }
    }

    // Set all remaining cells as fixed (can’t be changed by the player)
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (grid[row][col].getValue() != 0) {
                grid[row][col].setFixed(true);
            }
        }
    }
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
