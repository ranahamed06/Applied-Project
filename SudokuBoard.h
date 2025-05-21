#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H

#include <cstdlib>
#include "Cell.h"
#include "TreeNode.h" 

class SudokuBoard {
private:
    static const int SIZE = 9;
    static const int BOX_SIZE = 3;
    Cell grid[SIZE][SIZE];
    
    static int recursionDepth; 

    static int treeNodesVisited; 

    bool solveRecursive(int row, int col);
    bool solveBacktracking(TreeNode<SudokuBoard>* currentNode);

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
    bool solve(char c); 

    int getEmptyCount() const;

    void generateCompleteBoard();
    void createPuzzle(int difficulty);

    void saveState(int savedGrid[SIZE][SIZE]) const;
    void loadState(const int savedGrid[SIZE][SIZE]);
};

#endif // SUDOKUBOARD_H
