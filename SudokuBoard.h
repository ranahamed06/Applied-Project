//
// Created by Malak Abdelhalim on 04/05/2025.
//

#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H

#include <cstdlib>
#include "Cell.h"

class SudokuBoard {
private:
    static const int SIZE = 9;
    static const int BOX_SIZE = 3;
    Cell grid[SIZE][SIZE];
    //static int recursionDepth;
    static int recursionCalls;       // Total number of calls
    static int currentDepth;         // Current depth in the call stack
    static int maxRecursionDepth;    // Maximum depth reached

    bool solveRecursive(int row, int col);

public:
    SudokuBoard();

    void clear();
    Cell& getCell(int row, int col);
    const Cell& getCell(int row, int col) const;

    void setValue(int row, int col, int value, bool fixed = false);
    bool isValid(int row, int col, int value) const;
    bool isSolved() const;

    void updateCandidates(int row, int col, int value);
    void refreshCandidates();

    bool solve();

    int getEmptyCount() const;

    void generateCompleteBoard();
    void createPuzzle(int difficulty);

    void saveState(int savedGrid[SIZE][SIZE]) const;
    void loadState(const int savedGrid[SIZE][SIZE]);

    std::pair<int, int> findCellWithFewestChoices();

    // Function to count the number of valid choices for a given cell
    int countValidChoices(int row, int col) const;

};

#endif //SUDOKUBOARD_H
