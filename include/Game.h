#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Player.h"
#include "Monster.h"
#include "Character.h"

/**
 * Game class - main controller/orchestrator
 * Implements Facade pattern - provides simple interface to complex subsystem
 * Manages game loop, turn order, and win/loss conditions
 */
class Game {
private:
    Map* map;                       // The game map (composition - we own it)
    Player* player;                 // The player character (composition)
    Monster* monster;               // The monster character (composition)
    Character* activeCharacter;     // Pointer to currently active character
    bool gameOver;                  // Game over flag
    bool playerWon;                 // Did player win?
    int turnCount;                  // Number of turns elapsed

    // Private helper methods
    void setupMap();
    void playerTurn();
    void monsterTurn();
    void checkGameOver();
    void switchTurn();
    void displayStatus() const;
    void displayGameOver() const;

public:
    // Constructor and Destructor
    Game(int rows, int cols);
    ~Game();

    // Prevent copying
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    // Main game loop
    void run();

    // Public query methods (for Character.sense())
    std::vector<int> getPlayerPosition() const;
    std::vector<int> getExitPosition() const;
    bool isGameOver() const;
    bool playerWins() const;
};

#endif // GAME_H