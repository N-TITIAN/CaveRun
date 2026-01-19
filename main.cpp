#include "Game.h"
#include <iostream>

int main() {
    int rows, cols;

    std::cout << "========================================" << std::endl;
    std::cout << "         CAVE RUN GAME SETUP" << std::endl;
    std::cout << "========================================" << std::endl;

    // Get map dimensions from user
    std::cout << "\nEnter cave dimensions:" << std::endl;
    std::cout << "Number of columns (width): ";
    std::cin >> cols;
    std::cout << "Number of rows (height): ";
    std::cin >> rows;

    // Validate input
    if (cols < 3 || rows < 3) {
        std::cout << "\nError: Cave must be at least 3x3!" << std::endl;
        return 1;
    }

    if (cols > 20 || rows > 20) {
        std::cout << "\nWarning: Large caves may be difficult to navigate!" << std::endl;
    }

    // Create and run game
    Game game(rows, cols);
    game.run();

    return 0;
}