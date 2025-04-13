#include "SudokuBoard.h"
using namespace std;

// Constructor to initialize empty board (all zeros)
SudokuBoard::SudokuBoard() {
    for (int i = 0; i < SIZE; i++) {
        Vector<int> row;
        for (int j = 0; j < SIZE; j++) {
            row.push_back(0); // Initialize all cells with 0
        }
        board.push_back(row);
    }
}

// Copy constructor for BacktrackTree integration
SudokuBoard::SudokuBoard(const SudokuBoard& other) {
    for (int i = 0; i < SIZE; i++) {
        Vector<int> row;
        for (int j = 0; j < SIZE; j++) {
            row.push_back(other.board[i][j]); // Copy each cell
        }
        board.push_back(row);
    }
}



// Display the current board
void SudokuBoard::printBoard() const {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            std::cout << board[r][c] << " ";
            if (c == 2 || c == 5) std::cout << "| "; // Vertical separator
        }
        std::cout << std::endl;
        if (r == 2 || r == 5) {
            std::cout << "---------------------" << std::endl; // Horizontal separator
        }
    }
}

// Validate move against Sudoku rules
bool SudokuBoard::isValidMove(int row, int col, int num) const {
    // Check row
    for (int c = 0; c < SIZE; c++) {
        if (board[row][c] == num) return false;
    }

    // Check column
    for (int r = 0; r < SIZE; r++) {
        if (board[r][col] == num) return false;
    }

    // Check subgrid
    int boxRowStart = (row / 3) * 3;
    int boxColStart = (col / 3) * 3;
    for (int r = boxRowStart; r < boxRowStart + 3; r++) {
        for (int c = boxColStart; c < boxColStart + 3; c++) {
            if (board[r][c] == num) return false;
        }
    }

    return true;
}

// Backtracking solver
bool SudokuBoard::solveSudoku() {
    int row, col;
    if (!findEmptyCell(row, col)) return true; // No empty cells, puzzle solved!

    for (int num = 1; num <= SIZE; num++) {
        if (isValidMove(row, col, num)) {
            board[row][col] = num;

            if (solveSudoku()) return true;

            board[row][col] = 0; // Backtrack
        }
    }
    return false;
}

// Find next empty cell (returns true if found)
bool SudokuBoard::findEmptyCell(int& row, int& col) const {
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) return true;
        }
    }
    return false;
}

// Set cell value
void SudokuBoard::setCell(int row, int col, int num) {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
        board[row][col] = num;
    } else {
        throw std::out_of_range("Invalid cell coordinates");
    }
}

// Get cell value
int SudokuBoard::getCell(int row, int col) const {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
        return board[row][col];
    } else {
        throw std::out_of_range("Invalid cell coordinates");
    }
}

// Check if the board is fully filled
bool SudokuBoard::isComplete() const {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (board[r][c] == 0) return false;
        }
    }
}

bool SudokuBoard::solveWithTree() {
    BacktrackTreeNode* root = new BacktrackTreeNode(this, nullptr);
    bool solved = solveRecursive(root);
    if (solved) {
        BacktrackTreeNode* current = root;
        while (current->getNumChildren() > 0) {
            current = current->getChild(0);  // follow path
        }
        *this = *(current->getBoard());  // Copy solved board into the current one
    }
    delete root;
    return solved;
}


bool SudokuBoard::solveRecursive(BacktrackTreeNode* node) {
    SudokuBoard* currentBoard = node->getBoard();
    int row, col;

    if (!currentBoard->findEmptyCell(row, col)) {
        return true;  // Board is solved
    }

    for (int num = 1; num <= 9; ++num) {
        if (currentBoard->isValidMove(row, col, num)) {
            SudokuBoard nextState = *currentBoard;  // Copy current board
            nextState.setCell(row, col, num);

            node->addChild(&nextState);  // Add to tree
            if (solveRecursive(node->getChild(node->getNumChildren() - 1))) {
                return true;  // Found solution down this path
            }
        }
    }

    return false;  // Trigger backtracking
}

bool SudokuBoard::generateSolvedBoard() {
  solveSudoku();
}
void SudokuBoard::makeMove(int row, int col, int num) {
  setCell(row, col, num);
}

