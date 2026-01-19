#include "Game.h"
#include "PoisonRoom.h"
#include "TrapRoom.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

Game::Game(int rows, int cols)
    : gameOver(false), playerWon(false), turnCount(0) {
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "       WELCOME TO CAVE RUN!" << std::endl;
    std::cout << "========================================" << std::endl;
    
    // Create map
    map = new Map(rows, cols);
    
    // Set exit position (top-right)
    map->setExitPosition({cols, rows});
    
    // Setup map with rooms
    setupMap();
    
    // Create player at bottom-left [1, 1]
    player = new Player({1, 1});
    Room* startRoom = map->getRoom(1, 1);
    player->setRoom(startRoom);
    
    // Create monster at middle of map
    int monsterCol = cols / 2;
    int monsterRow = rows / 2;
    monster = new Monster({monsterCol, monsterRow});
    Room* monsterStartRoom = map->getRoom(monsterCol, monsterRow);
    monster->setRoom(monsterStartRoom);
    
    // Player starts as active character
    activeCharacter = player;
    
    std::cout << "\nGame initialized!" << std::endl;
    std::cout << "Player starts at: [1, 1]" << std::endl;
    std::cout << "Monster starts at: [" << monsterCol << ", " << monsterRow << "]" << std::endl;
    std::cout << "Exit is at: [" << cols << ", " << rows << "]" << std::endl;
    std::cout << "\nObjective: Reach the exit while avoiding the monster!" << std::endl;
    std::cout << "You have " << player->getHealth() << " health points." << std::endl;
}

Game::~Game() {
    delete map;
    delete player;
    delete monster;
}

void Game::setupMap() {
    std::vector<int> dims = map->getDimensions();
    int cols = dims[0];
    int rows = dims[1];
    
    std::cout << "\nGenerating " << cols << "x" << rows << " cave..." << std::endl;
    
    // Seed random if not already done
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }
    
    // Create rooms for each position
    for (int row = 1; row <= rows; row++) {
        for (int col = 1; col <= cols; col++) {
            std::vector<int> pos = {col, row};
            Room* room = nullptr;
            
            // Start position [1,1] and exit position must be normal rooms
            if ((col == 1 && row == 1) || (col == cols && row == rows)) {
                room = new Room(pos);
            } else {
                // Random room type
                int randomValue = rand() % 100;
                
                if (randomValue < 60) {
                    // 60% chance of normal room
                    room = new Room(pos);
                } else if (randomValue < 85) {
                    // 25% chance of poison room
                    room = new PoisonRoom(pos);
                } else {
                    // 15% chance of trap room (damage = 15)
                    room = new TrapRoom(pos, 15);
                }
            }
            
            map->addRoom(room);
        }
    }
    
    std::cout << "Cave generated successfully!" << std::endl;
}

void Game::playerTurn() {
    std::cout << "\n========== PLAYER TURN " << (turnCount + 1) << " ==========" << std::endl;
    
    player->resetMoves();
    
    while (player->getMoves() > 0 && !gameOver) {
        displayStatus();
        
        // Get player input
        std::cout << "\nEnter direction (dx dy) where dx,dy are -1, 0, or 1: ";
        int dx, dy;
        
        if (!(std::cin >> dx >> dy)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter two numbers." << std::endl;
            continue;
        }
        
        // Validate input range
        if (dx < -1 || dx > 1 || dy < -1 || dy > 1) {
            std::cout << "Invalid direction! Values must be -1, 0, or 1." << std::endl;
            continue;
        }
        
        // Set player direction and move
        player->setMoveDirection({dx, dy});
        player->sense(*this);
        player->move(*map);
        
        // Check game over after each move
        checkGameOver();
    }
    
    // Update phase (poison damage, cure attempt)
    if (!gameOver) {
        std::cout << "\n--- End of turn update ---" << std::endl;
        player->update();
        checkGameOver();
    }
}

void Game::monsterTurn() {
    std::cout << "\n========== MONSTER TURN ==========" << std::endl;
    
    monster->resetMoves();
    
    while (monster->getMoves() > 0 && !gameOver) {
        monster->sense(*this);
        monster->move(*map);
        monster->update();
        
        checkGameOver();
    }
}

void Game::checkGameOver() {
    // Check if player reached exit
    if (player->getPosition() == map->getExitPosition()) {
        gameOver = true;
        playerWon = true;
        return;
    }
    
    // Check if player is dead
    if (!player->isAlive()) {
        gameOver = true;
        playerWon = false;
        return;
    }
    
    // Check if monster caught player
    if (monster->getPosition() == player->getPosition()) {
        gameOver = true;
        playerWon = false;
        std::cout << "\n!!! MONSTER CAUGHT YOU !!!" << std::endl;
        return;
    }
}

void Game::switchTurn() {
    if (activeCharacter == player) {
        activeCharacter = monster;
    } else {
        activeCharacter = player;
        turnCount++;
    }
}

void Game::displayStatus() const {
    std::cout << "\n--- STATUS ---" << std::endl;
    std::cout << "Player: [" << player->getPosition()[0] << ", " 
              << player->getPosition()[1] << "] | Health: " << player->getHealth();
    if (player->getPoisonStatus()) {
        std::cout << " | POISONED!";
    }
    std::cout << " | Moves: " << player->getMoves() << std::endl;
    
    std::cout << "Monster: [" << monster->getPosition()[0] << ", " 
              << monster->getPosition()[1] << "]" << std::endl;
    
    std::cout << "Exit: [" << map->getExitPosition()[0] << ", " 
              << map->getExitPosition()[1] << "]" << std::endl;
}

void Game::displayGameOver() const {
    std::cout << "\n========================================" << std::endl;
    std::cout << "           GAME OVER!" << std::endl;
    std::cout << "========================================" << std::endl;
    
    if (playerWon) {
        std::cout << "\n   *** YOU ESCAPED THE CAVE! ***" << std::endl;
        std::cout << "   Congratulations! You WIN!" << std::endl;
    } else {
        if (!player->isAlive()) {
            std::cout << "\n   *** YOU DIED! ***" << std::endl;
            std::cout << "   Your health reached zero." << std::endl;
        } else {
            std::cout << "\n   *** CAUGHT BY MONSTER! ***" << std::endl;
            std::cout << "   The monster caught you!" << std::endl;
        }
        std::cout << "   Better luck next time!" << std::endl;
    }
    
    std::cout << "\nFinal Stats:" << std::endl;
    std::cout << "  Turns survived: " << turnCount << std::endl;
    std::cout << "  Final health: " << player->getHealth() << std::endl;
    std::cout << "========================================" << std::endl;
}

void Game::run() {
    // Display initial map
    map->display();
    
    // Main game loop
    while (!gameOver) {
        playerTurn();
        
        if (!gameOver) {
            switchTurn();
            monsterTurn();
            switchTurn();
        }
    }
    
    // Game over
    displayGameOver();
}

std::vector<int> Game::getPlayerPosition() const {
    return player->getPosition();
}

std::vector<int> Game::getExitPosition() const {
    return map->getExitPosition();
}

bool Game::isGameOver() const {
    return gameOver;
}

bool Game::playerWins() const {
    return playerWon;
}