#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

/**
 * Player class - represents the human-controlled character
 * Manages health, poison status, and user input for movement
 */
class Player : public Character {
private:
    int health;                      // Current health points
    bool isPoisoned;                 // Poison status flag
    int poisonDamage;                // Damage taken per turn when poisoned
    double cureChance;               // Probability of curing poison (0.0 to 1.0)
    std::vector<int> moveDirection;  // Direction set by user input

protected:
    // Implementation of pure virtual from Character
    std::vector<int> getDirection() override;

public:
    // Constructor
    Player(std::vector<int> startPos);

    // Health management
    int getHealth() const;
    void damage(int amount);
    bool isAlive() const;

    // Poison management
    void poison();
    void cure();
    bool getPoisonStatus() const;

    // Movement control
    void setMoveDirection(std::vector<int> dir);

    // Override Character methods
    void sense(Game& game) override;
    void move(Map& map) override;
    void update() override;

    void setRemainingMoves(int moves);
};

#endif // PLAYER_H