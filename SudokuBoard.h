#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H


#include <iostream>


#include "vector.h"
#include "vector.cpp" // Include implementation file





class SudokuBoard {
private:
    static const int SIZE = 9;  // 9*9 board
    Vector<Vector<int>> board;      // The Sudoku grid


public:
    SudokuBoard();  // Constructor to initialize the board
    SudokuBoard(const SudokuBoard& other); // Copy constructor

    
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
   
    //void clearBoard(); // clear the board
    
    bool generateSolvedBoard();    // Generate a completely solved board using backtracking
	bool solveWithTree();
    bool solveRecursive(BacktrackTreeNode* node);

    
};

#endif
