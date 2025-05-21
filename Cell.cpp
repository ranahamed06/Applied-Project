
#include "Cell.h"

Cell::Cell() : value(0), fixed(false) {
    // Initialize with all possible candidates (1-9)
    for (int i = 1; i <= 9; i++) {
        candidates.push_back(i);
    }
}

int Cell::getValue() const {
    return value;
}

void Cell::setValue(int newValue) {
    value = newValue;
    if (value != 0) {
        candidates.clear();
    }
}

bool Cell::isFixed() const {
    return fixed;
}

void Cell::setFixed(bool isFixed) {
    fixed = isFixed;
}

bool Cell::isEmpty() const {
    return value == 0;
}

const CustomVector<int>& Cell::getCandidates() const {
    return candidates;
}

void Cell::removeCandidate(int candidate) {
    for (int i = 0; i < candidates.size(); i++) {
        if (candidates[i] == candidate) {
            candidates.remove(i);
            break;
        }
    }
}

void Cell::clearCandidates() {
    candidates.clear();
}

bool Cell::hasCandidate(int candidate) const {
    for (int i = 0; i < candidates.size(); i++) {
        if (candidates[i] == candidate) {
            return true;
        }
    }
    return false;
}

void Cell::restoreCandidates() {
    candidates.clear();
    if (value == 0) {
        for (int i = 1; i <= 9; i++) {
            candidates.push_back(i);
        }
    }
} 
