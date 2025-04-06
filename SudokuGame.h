#ifndef SUDOKUGAME_H
#define SUDOKUGAME_H

#include "SudokuBoard.h"

class SudokuGame {
private:
    SudokuBoard board;  // The Sudoku board object
    static const int SIZE = 9;

public:
    void initializePuzzle();  // Initializes a puzzle on the board
    void startGame();  // Starts the game where the user plays
    SudokuBoard& getBoard() { return board; }  // Getter to access the board
    void autoSolve();  // Function to automatically solve the puzzle
    // Function to generate a new random puzzle
    void generateRandomPuzzle(int difficulty);
};

#endif
