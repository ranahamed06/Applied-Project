//
// Created by Malak Abdelhalim on 13/04/2025.
//

#ifndef BACKTRACKTREE_H
#define BACKTRACKTREE_H
#include "SudokuBoard.h"

//  This tree represents the different states of the Sudoku board during backtracking.
//  Each node holds a state, and child nodes represent decisions (placing a value in a cell).

<<<<<<< Updated upstream
#pragma once

class SudokuBoard; // Forward declaration

=======
>>>>>>> Stashed changes
class BacktrackTreeNode
{
public:
    SudokuBoard* boardState;           // Pointer to board state at this node
    BacktrackTreeNode* parent;         // Pointer to parent node
    BacktrackTreeNode** children;      // Dynamic array of pointers to children
    int numChildren;                   // Current number of children
    int capacity;                      // Allocated size of children array

    BacktrackTreeNode(SudokuBoard* state, BacktrackTreeNode* parentNode = nullptr);
    ~BacktrackTreeNode();

    void addChild(SudokuBoard* childState); // Adds a child node with a copy of board
    SudokuBoard* getBoard();                // Returns current board state
    BacktrackTreeNode* getParent();         // Returns parent pointer
    BacktrackTreeNode* getChild(int index); // Returns pointer to child at index
    int getNumChildren() const;
};

#endif //BACKTRACKTREE_H
