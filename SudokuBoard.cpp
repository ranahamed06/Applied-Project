#include "SudokuBoard.h"

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
int SudokuBoard::recursionCalls = 0;
int SudokuBoard::currentDepth = 0;
int SudokuBoard::maxRecursionDepth = 0;

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

bool SudokuBoard::solveBacktracking(TreeNode<SudokuBoard>* currentNode) {
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

bool SudokuBoard::solve(char c) {
    if (c == 'v' || c == 'V')
    {
        return solveRecursive(0, 0);
    }
    if (c == 't' || c == 'T')
    {
        TreeNode<SudokuBoard>* root = new TreeNode<SudokuBoard>(*this);
        bool result = solveBacktracking(root);
        delete root; // prevent memory leak
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
    solve(); // solves the board
}

// Remove cells to create a puzzle of the specified difficulty
void SudokuBoard::createPuzzle(int difficulty) {
    // First, generate a complete valid board
    generateCompleteBoard();

    // Then, remove cells based on difficulty (More removed cells -> harder puzzle)
    int cellsToRemove;
    switch (difficulty) {
        case 1: // Easy
            cellsToRemove = 40; // Leaves about 41 clues (easy)
        break;
        case 2: // Medium
            cellsToRemove = 50; // Leaves about 31 clues (medium)
        break;
        case 3: // Hard
            cellsToRemove = 60; // Leaves about 21 clues (hard)
        break;
        default:
            cellsToRemove = 45;
    }

    // Remember which cells have been removed
    // keeps track of which cells have already been removed to avoid removing the same cell multiple times
    bool removed[SIZE][SIZE] = {{false}}; // unspecified elements are initialized as false (not removed)

    // Remove cells randomly while ensuring puzzle is solvable and has a unique solution
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

        // Make a copy of the board to test whether the puzzle is still solvable after removal
        SudokuBoard tempBoard;

        // check that the current removal doesn't make the puzzle unsolvable

        // Copy the current state of the board
        for (int r = 0; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                tempBoard.setValue(r, c, grid[r][c].getValue());
            }
        }

        // If the board is still solvable, keep the removal
        if (tempBoard.solve()) {
            cellsToRemove--;
        } else {
            // Restore the cell (undo removal)
            grid[row][col].setValue(temp);
            removed[row][col] = false;
        }
    }

    // After all removals,
    // Set all remaining cells as fixed (can’t be changed by the player)


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
