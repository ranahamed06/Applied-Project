
#include "SudokuGame.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

// Constructor
SudokuGame::SudokuGame() : gameOver(false), moves(0) {
    cout << "\n===================================\n";
    cout << "===        SUDOKU GAME          ===\n";
    cout << "===================================\n";
}

void SudokuGame::displayBoard() const {
    cout << "\n     ";
    for (int col = 0; col < SIZE; col++) {
        if ((col + 1) % BOX_SIZE == 0) {
            cout << (col + 1) << "    ";
        } else
        cout << (col + 1) << "   ";
    }
    cout << "\n   ";

    for (int col = 0; col < SIZE; col++) {
        cout << "----";
    }
    cout << "---\n";

    for (int row = 0; row < SIZE; row++) {
        cout << " " << (row + 1) << " |";

        for (int col = 0; col < SIZE; col++) {
            const Cell& cell = board.getCell(row, col);

            if (cell.getValue() == 0) {
                cout << "   |";
            } else {
                if (cell.isFixed()) {
                    cout << " \033[1m" << cell.getValue() << "\033[0m |"; // Bold for fixed cells
                } else {
                    cout << " " << cell.getValue() << " |"; // print user input normally
                }
            }

            if ((col + 1) % BOX_SIZE == 0 && col < SIZE - 1) {
                cout << "|";
            }
        }

        cout << "\n   ";

        for (int col = 0; col < SIZE; col++) {
            cout << "----";
        }
        cout << "---\n";

        if ((row + 1) % BOX_SIZE == 0 && row < SIZE - 1) {
            cout << "   ";
            for (int col = 0; col < SIZE; col++) {
                cout << "----";
            }
            cout << "---\n";
        }
    }
}

void SudokuGame::showCandidates(int row, int col) const {
    const Cell& cell = board.getCell(row, col); // retrieves cell at specified position

    if (!cell.isEmpty()) {
        cout << "Cell already has value " << cell.getValue() << "\n";
        return;
    }

    const CustomVector<int>& candidates = cell.getCandidates(); // retrieves reference to candidates

    cout << "Candidates for cell (" << (row + 1) << "," << (col + 1) << "): ";

    if (candidates.empty()) {
        cout << "No valid candidates\n";
    } else {
        for (int i = 0; i < candidates.size(); i++) {
            cout << candidates[i];
            if (i < candidates.size() - 1) { // no comma after last candidate
            cout << ", ";
            }
        }
        cout << "\n";
    }
}

void SudokuGame::saveCurrentState() {
    board.saveState(savedState);
}

void SudokuGame::restoreSavedState() {
    board.loadState(savedState);
}

// validates player moves
void SudokuGame::getInput(int& row, int& col, int& value) {
    while (true) {
        cout << "Enter row (1-9): ";
        cin >> row;

        if (cin.fail() || row < 1 || row > 9) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid row. Please enter a number between 1 and 9.\n";
            continue; // restarts loop
        }

        cout << "Enter column (1-9): ";
        cin >> col;

        if (cin.fail() || col < 1 || col > 9) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid column. Please enter a number between 1 and 9.\n";
            continue;
        }

        // Convert to 0-based indices
        row--;
        col--;

        // Check if the cell is fixed
        if (board.getCell(row, col).isFixed()) {
            cout << "That cell is fixed and cannot be modified.\n";
            continue;
        }

        cout << "Enter value (1-9, or 0 to clear): ";
        cin >> value;

        if (cin.fail() || value < 0 || value > 9) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid value. Please enter a number between 0 and 9.\n";
            continue;
        }

        // If clearing the cell or if the value is valid, accept the input
        if (value == 0 || board.isValid(row, col, value)) {
            break;
        } else {
            cout << "Invalid move. The value " << value << " is not allowed in this position.\n";
        }
    }
}

void SudokuGame::displayTime() const {
    time_t currentTime = time(nullptr);
    int elapsedSeconds = static_cast<int>(difftime(currentTime, startTime));

    int hours = elapsedSeconds / 3600;
    int minutes = (elapsedSeconds % 3600) / 60;
    int seconds = elapsedSeconds % 60;

    cout << "Time: ";
    if (hours > 0) {
        cout << hours << "h ";
    }
    cout << minutes << "m " << seconds << "s\n";
}

// suggests the correct value for the first empty cell
void SudokuGame::displayHint() {
    // Find the first empty cell
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board.getCell(row, col).isEmpty()) {
                // Save current state
                SudokuBoard tempBoard = board;

                // Try to solve the board
                if (board.solve()) {
                    int correctValue = board.getCell(row, col).getValue();
                    // Restore original board
                    board = tempBoard;
                    cout << "Hint: Try placing " << correctValue << " at position ("
                              << (row+1) << "," << (col+1) << ").\n";
                    return;
                } else {
                    cout << "Couldn't generate a hint. The current board might not be solvable.\n";
                    return;
                }
            }
        }
    }
    cout << "The board is already complete!\n";
}

void SudokuGame::displayHelp() const {
    cout << "\n=== SUDOKU HELP ===\n";
    cout << "p: Place a number on the board\n";
    cout << "c: Show candidates for a cell\n";
    cout << "h: Get a hint\n";
    cout << "u: Undo last move\n";
    cout << "s: Solve the puzzle\n";
    cout << "r: Restart the game\n";
    cout << "q: Quit the game\n";
    cout << "?: Show this help menu\n";
    cout << "===================\n\n";
}

int SudokuGame::chooseDifficulty() {
    int difficulty;

    cout << "\n=== CHOOSE DIFFICULTY ===\n";
    cout << "1: Easy\n";
    cout << "2: Medium\n";
    cout << "3: Hard\n";
    cout << "=========================\n";

    while (true) {
        cout << "Enter your choice (1-3): ";
        cin >> difficulty;

        if (cin.fail() || difficulty < 1 || difficulty > 3) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid choice. Please enter a number between 1 and 3.\n";
        } else {
            break;
        }
    }

    return difficulty;
}

void SudokuGame::startNewGame() {
    int difficulty = chooseDifficulty();

    board.clear();
    board.createPuzzle(difficulty);

    gameOver = false;
    moves = 0;
    startTime = time(nullptr);

    // Save initial state
    saveCurrentState();
}

void SudokuGame::congratulate() const {
    cout << "\n******\n";
    cout << "*                            *\n";
    cout << "  CONGRATULATIONS! YOU WIN!  \n";
    cout << "*                            *\n";
    cout << "******\n\n";

    time_t currentTime = time(nullptr);
    int elapsedSeconds = static_cast<int>(difftime(currentTime, startTime));

    int hours = elapsedSeconds / 3600;
    int minutes = (elapsedSeconds % 3600) / 60;
    int seconds = elapsedSeconds % 60;

    cout << "You completed the puzzle in " << moves << " moves.\n";
    cout << "Your time: ";
    if (hours > 0) {
        std::cout << hours << " hours, ";
    }
    cout << minutes << " minutes, and " << seconds << " seconds.\n\n";
}

// player interaction, game state transitions, screen updates
void SudokuGame::run() {
    startNewGame();

        char choice;
        bool quit = false;

        while (!quit) {
            // Clear the screen
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif

            cout << "\n===================================\n";
            cout << "===       SUDOKU GAME          ===\n";
            cout << "===================================\n";

            displayTime();
            cout << "Moves: " << moves << "\n";
            cout << "Empty cells: " << board.getEmptyCount() << "\n";

            displayBoard();

            if (gameOver) {
                congratulate();

                cout << "Play again? (y/n): ";
                cin >> choice;

                if (choice == 'y' || choice == 'Y') {
                    startNewGame();
                } else {
                    quit = true;
                }

                continue;
            }

            cout << "\n=== MENU ===\n";
            cout << "p: Place a number\n";
            cout << "c: Show candidates\n";
            cout << "h: Get a hint\n";
            cout << "u: Undo last move\n";
            cout << "s: Solve the puzzle\n";
            cout << "r: Restart the game\n";
            cout << "q: Quit the game\n";
            cout << "?: Show help\n";
            cout << "=============\n";

            cout << "Enter your choice: ";
            cin >> choice;

            int row, col, value;

            switch (choice) {
                case 'p':
                case 'P':
                    // Place a number
                    saveCurrentState();
                    getInput(row, col, value);
                    board.setValue(row, col, value);
                    moves++;

                    // Check if the puzzle is solved
                    if (board.getEmptyCount() == 0 && board.isSolved()) {
                        gameOver = true;
                    }
                    break;

                case 'c':
                case 'C':
                    // Show candidates for a cell
                    while (true) {
                        cout << "Enter row (1-9): ";
                        cin >> row;

                        if (cin.fail() || row < 1 || row > 9) {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Invalid row. Please enter a number between 1 and 9.\n";
                            continue;
                        }

                        cout << "Enter column (1-9): ";
                        cin >> col;

                        if (cin.fail() || col < 1 || col > 9) {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Invalid column. Please enter a number between 1 and 9.\n";
                            continue;
                        }

                        // Convert to 0-based indices
                        row--;
                        col--;

                        showCandidates(row, col);
                        break;
                    }

                    cout << "Press Enter to continue...";
                    cin.ignore(10000, '\n');
                    cin.get();
                    break;

                case 'h':
                case 'H':
                    // Get a hint
                    displayHint();
                    cout << "Press Enter to continue...";
                    cin.ignore(10000, '\n');
                    cin.get();
                    break;

                case 'u':
                case 'U':
                    // Undo last move
                    restoreSavedState();
                    cout << "Move undone.\n";
                    cout << "Press Enter to continue...";
                    cin.ignore(10000, '\n');
                    cin.get();
                    break;

                case 's':
                case 'S':
                    // Solve the puzzle
                    {
                        cout << "Are you sure you want to solve the puzzle? (y/n): ";
                        char confirm;
                        cin >> confirm;
                        if (confirm == 'y' || confirm == 'Y') {
                            cout << "Would you like to solve the puzzle using the custom vector or the tree? enter (v/t): ";
                            char pick;
                            cin >> pick;
                                saveCurrentState();

                                // Start timing
                                auto start = std::chrono::steady_clock::now();

                                if (board.solve(pick)) {
                                    // End timing
                                    auto end = std::chrono::steady_clock::now();
                                    std::chrono::duration<double> elapsed = end - start;

                                    cout << "Puzzle solved in " << elapsed.count() << " seconds.\n";
                                }
                                if (board.solve(pick)) {
                                    cout << "Puzzle solved!\n";
                                    // Display the solved board
                                    displayBoard();
                                    cout << "Press Enter to continue...";
                                    cin.ignore(10000, '\n');
                                    cin.get();
                                    gameOver = true;
                                } else {
                                    cout << "The puzzle cannot be solved from the current state.\n";
                                    restoreSavedState();
                                    cout << "Press Enter to continue...";
                                    cin.ignore(10000, '\n');
                                    cin.get();
                                }
                        }
                    }
                    break;


                case 'r':
                case 'R':
                    // Restart the game
                    {
                        cout << "Are you sure you want to restart the game? (y/n): ";
                        char confirm;
                        cin >> confirm;

                        if (confirm == 'y' || confirm == 'Y') {
                            startNewGame();
                        }
                    }
                    break;

                case 'q':
                case 'Q':
                    // Quit the game
                    {
                        cout << "Are you sure you want to quit? (y/n): ";
                        char confirm;
                        cin >> confirm;

                        if (confirm == 'y' || confirm == 'Y') {
                            quit = true;
                        }
                    }
                    break;

                case '?':
                    // Show help
                    displayHelp();
                    cout << "Press Enter to continue...";
                    cin.ignore(10000, '\n');
                    cin.get();
                    break;

                default:
                    cout << "Invalid choice. Press Enter to continue...";
                    cin.ignore(10000, '\n');
                    cin.get();
                    break;
            }
        }

        cout << "\nThank you for playing Sudoku!\n";
}