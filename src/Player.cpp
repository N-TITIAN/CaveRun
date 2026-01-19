#include "Player.h"
#include "Room.h"
#include "Map.h"
#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Player::Player(std::vector<int> startPos)
    : Character(startPos, 2, "BLUE", 'P'),
      health(100), isPoisoned(false), poisonDamage(5), cureChance(0.3),
      moveDirection({0, 0}) {
    // Seed random number generator (do this once)
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }
}

int Player::getHealth() const {
    return health;
}

void Player::damage(int amount) {
    health -= amount;
    if (health < 0) {
        health = 0;
    }
    std::cout << "Player took " << amount << " damage! Health: " << health << std::endl;
}

bool Player::isAlive() const {
    return health > 0;
}

void Player::poison() {
    isPoisoned = true;
    std::cout << "Player is POISONED!" << std::endl;
}

void Player::cure() {
    isPoisoned = false;
    std::cout << "Player has been CURED!" << std::endl;
}

bool Player::getPoisonStatus() const {
    return isPoisoned;
}

void Player::setMoveDirection(std::vector<int> dir) {
    moveDirection = dir;
}

std::vector<int> Player::getDirection() {
    return moveDirection;
}

void Player::sense(Game& game) {
    // Player doesn't need to sense - controlled by user
    // This method exists to satisfy the interface
}

void Player::move(Map& map) {
    // Call parent move implementation
    Character::move(map);
    
    // After moving, visit the room (triggers room effects)
    if (currentRoom != nullptr) {
        currentRoom->visit(this);
    }
}

void Player::update() {
    // Apply poison damage if poisoned
    if (isPoisoned) {
        std::cout << "Poison damage applied!" << std::endl;
        damage(poisonDamage);
        
        // Attempt to cure
        double randomValue = static_cast<double>(rand()) / RAND_MAX;
        if (randomValue < cureChance) {
            cure();
        } else {
            std::cout << "Still poisoned..." << std::endl;
        }
    }
}

void Player::setRemainingMoves(int moves) {
    movesRemaining = moves;
}