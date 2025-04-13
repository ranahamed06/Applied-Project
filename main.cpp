#include <iostream>
#include "SudokuBoard.h"

void displayMenu() {
    std::cout << "\n=== Sudoku Game ===" << std::endl;
    std::cout << "1. Display Current Board" << std::endl;
    std::cout << "2. Set a Cell Value" << std::endl;
    std::cout << "3. Solve the Puzzle" << std::endl;
    std::cout << "4. Reset the Board" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    SudokuBoard board; // Create an empty Sudoku board
    int choice;

    while (true) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
        case 1: { // Display Current Board
            std::cout << "\nCurrent Board:" << std::endl;
            board.printBoard();
            break;
        }
        case 2: { // Set a Cell Value
            int row, col, num;
            std::cout << "\nEnter row (1-9): ";
            std::cin >> row;
            std::cout << "Enter column (1-9): ";
            std::cin >> col;
            std::cout << "Enter number (1-9): ";
            std::cin >> num;

            try {
                if (board.isValidMove(row - 1, col - 1, num)) {
                    board.setCell(row - 1, col - 1, num);
                    std::cout << "Value set successfully!" << std::endl;
                } else {
                    std::cout << "Invalid move! The number conflicts with Sudoku rules." << std::endl;
                }
            } catch (const std::out_of_range& e) {
                std::cout << "Error: " << e.what() << ". Please enter valid coordinates." << std::endl;
            }
            break;
        }
        case 3: { // Solve the Puzzle
            if (board.solveSudoku()) {
                std::cout << "\nSolved Board:" << std::endl;
                board.printBoard();
            } else {
                std::cout << "\nNo solution exists for the current puzzle!" << std::endl;
            }
            break;
        }
        case 4: { // Reset the Board
            board = SudokuBoard(); // Reset to a new empty board
            std::cout << "\nThe board has been reset!" << std::endl;
            break;
        }
        case 5: { // Exit
            std::cout << "\nExiting the game. Goodbye!" << std::endl;
            return 0; // Exit program
        }
        default:
            std::cout << "\nInvalid choice! Please select a valid option." << std::endl;
        }
    }

    return 0;
}
