
#ifndef CELL_H
#define CELL_H

#include "CustomVector.h"

// Represents a single Sudoku cell
class Cell {
private:
    int value;  // 0 represents empty
    bool fixed; // Whether this is a fixed/given cell
    CustomVector<int> candidates; // Candidate values for this cell

public:
    Cell();

    int getValue() const;
    void setValue(int newValue);

    bool isFixed() const;
    void setFixed(bool isFixed);

    bool isEmpty() const;

    const CustomVector<int>& getCandidates() const;
    void removeCandidate(int candidate);
    void clearCandidates();
    bool hasCandidate(int candidate) const;
    void restoreCandidates();
};

#endif //CELL_H
 
