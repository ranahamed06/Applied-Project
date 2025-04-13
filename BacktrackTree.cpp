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

BacktrackTreeNode::~BacktrackTreeNode() {
    delete boardState;

    for (int i = 0; i < numChildren; i++) {
        delete children[i];
    }
    delete[] children;
}

void BacktrackTreeNode::addChild(SudokuBoard* childState) {
    // Resize children array if full
    if (numChildren >= capacity) {
        capacity *= 2;
        BacktrackTreeNode** newChildren = new BacktrackTreeNode*[capacity];
        for (int i = 0; i < numChildren; i++) {
            newChildren[i] = children[i];
        }
        delete[] children;
        children = newChildren;
    }

    BacktrackTreeNode* childNode = new BacktrackTreeNode(childState, this);
    children[numChildren++] = childNode;
}

SudokuBoard* BacktrackTreeNode::getBoard() {
    return boardState;
}

BacktrackTreeNode* BacktrackTreeNode::getParent() {
    return parent;
}

BacktrackTreeNode* BacktrackTreeNode::getChild(int index) {
    if (index >= 0 && index < numChildren) {
        return children[index];
    }
    return nullptr;
}

int BacktrackTreeNode::getNumChildren() const {
    return numChildren;
}