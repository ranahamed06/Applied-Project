
#ifndef SUDOKUGAME_H
#define SUDOKUGAME_H

#include <iostream>
#include <ctime>
#include "SudokuBoard.h"
#include "Cell.h"
#include "CustomVector.h"
#include "TreeNode.h"

class SudokuGame {
private:
    static const int SIZE = 9;
    static const int BOX_SIZE = 3;

    SudokuBoard board;
    int savedState[SIZE][SIZE]; // For undo functionality
    bool gameOver;
    int moves;
    time_t startTime;

    void displayBoard() const;
    void showCandidates(int row, int col) const;
    void saveCurrentState();
    void restoreSavedState();
    void getInput(int& row, int& col, int& value);
    void displayTime() const;
    void displayHint();
    void displayHelp() const;
    int chooseDifficulty();
    void startNewGame();
    void congratulate() const;

public:
    SudokuGame();
    void run();
};

#endif // SUDOKUGAME_H
