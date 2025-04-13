#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H


#include <iostream>
<<<<<<< Updated upstream
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
=======
#include "vector.h"
#include "vector.cpp" // Include implementation file

class SudokuBoard { 

    static const int SIZE = 9;  // 9*9 board
    Vector<Vector<int>> board;      // The Sudoku grid


public:
    SudokuBoard();  // Constructor to initialize the board
    SudokuBoard(const SudokuBoard& other); // Copy constructor
>>>>>>> Stashed changes
    
    // functons 
    void printBoard() const;  // Display the current board
    
        //setter and getter
    void setCell(int row, int col, int value);  
    int getCell(int row, int col) const;

    bool isValidMove(int row, int col, int num) const;  // Validate a move
    bool findEmptyCell(int &row, int &col) const; // check for empty set

    bool solveSudoku();
    bool isComplete() const;  // Check if no empty cells left
    void makeMove(int row, int col, int num);  // Place a number in a cell
   
    void clearBoard(); // clear the board
    
    bool generateSolvedBoard();    // Generate a completely solved board using backtracking

    
    // Add a getter for a specific cell to allow for checking the puzzle state during random generation
<<<<<<< Updated upstream
    int getCell(int row, int col) const;
    
=======
>>>>>>> Stashed changes
    
};

#endif
