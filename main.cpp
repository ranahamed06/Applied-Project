#include <iostream>
#include <ctime>
#include "SudokuGame.h"

int main() {
    // Set random seed
    srand(static_cast<unsigned int>(time(nullptr)));

    SudokuGame game;
    game.run();

    return 0;
}

