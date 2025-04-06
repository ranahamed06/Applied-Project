#include <iostream>
#include "SudokuGame.h"
#include "SudokuBoard.h"

using namespace std;

int main() {
    SudokuGame game;
    SudokuBoard board;

    // Print a welcome message
    cout << "Welcome to Sudoku!" << endl;

    // Ask user for difficulty level (1: Easy, 2: Medium, 3: Hard)
    int difficulty;
    cout << "Choose difficulty level (1: Easy, 2: Medium, 3: Hard): ";
    cin >> difficulty;

    // Initialize the game with a random puzzle
    game.generateRandomPuzzle(difficulty);
    game.startGame();

    string replay;
    cout << "Would you like to play a new game? (Yes/No): ";
    cin >> replay;

    while (replay != "No" && replay != "no") {
        if (replay == "Yes" || replay == "yes") {
            game.generateRandomPuzzle(difficulty); // Generate a new puzzle
            game.startGame();
            cout << "Would you like to play a new game? (Yes/No): ";
            cin >> replay;
        } else {
            break;
        }
    }

    return 0;
}

