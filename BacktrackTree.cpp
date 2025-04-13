//
// Created by Malak Abdelhalim on 13/04/2025.
//

#include "BacktrackTree.h"
#include "SudokuBoard.h"

#include <iostream> // Only used for debugging/logging purposes

BacktrackTreeNode::BacktrackTreeNode(SudokuBoard* state, BacktrackTreeNode* parentNode)
    : boardState(nullptr), parent(parentNode), children(nullptr), numChildren(0), capacity(2) {

    // Deep copy of SudokuBoard (you need to implement a copy constructor in SudokuBoard)
    boardState = new SudokuBoard(*state);

    children = new BacktrackTreeNode*[capacity];
}
