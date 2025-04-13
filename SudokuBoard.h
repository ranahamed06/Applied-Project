#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H


#include <iostream>
#include "BacktrackTreeNode.h"

class SudokuBoard {
    static const int SIZE = 9;  // Size of the board (9x9)
    int board[SIZE][SIZE];      // The Sudoku grid
    bool solveRecursive(BacktrackTreeNode* node); //new
public:
    SudokuBoard();  // Constructor to initialize the board
    SudokuBoard(const SudokuBoard& other); //new
    void setCell(int row, int col, int value);  // Declaration of the setCell function
    void printBoard();  // Display the current board
    bool isValidMove(int row, int col, int num);  // Validate a move
    bool findEmptyCell(int &row, int &col);
    bool solveSudoku();
    bool solveWithTree(); //new
    bool isComplete();  // Check if the board is complete (no empty cells)
    void makeMove(int row, int col, int num);  // Place a number in a 
    // Clears the board
    void clearBoard();
    
    // Generate a completely solved board using backtracking
    bool generateSolvedBoard();
    
    // Add a getter for a specific cell to allow for checking the puzzle state during random generation
    int getCell(int row, int col) const;
    
    
};

#endif
