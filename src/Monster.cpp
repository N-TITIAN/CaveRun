#include "Monster.h"
#include "Game.h"
#include <cmath>
#include <iostream>

Monster::Monster(std::vector<int> startPos)
    : Character(startPos, 1, "RED", 'M'),
      playerPosition({0, 0}), exitPosition({0, 0}) {
}

double Monster::calculateDistance(std::vector<int> pos1, std::vector<int> pos2) const {
    int dx = pos2[0] - pos1[0];
    int dy = pos2[1] - pos1[1];
    return sqrt(dx * dx + dy * dy);
}

void Monster::sense(Game& game) {
    // Query game for player and exit positions
    playerPosition = game.getPlayerPosition();
    exitPosition = game.getExitPosition();
    
    std::cout << "\nMonster sensing..." << std::endl;
    std::cout << "  Player at: [" << playerPosition[0] << ", " << playerPosition[1] << "]" << std::endl;
    std::cout << "  Exit at: [" << exitPosition[0] << ", " << exitPosition[1] << "]" << std::endl;
}

std::vector<int> Monster::getDirection() {
    // Calculate distances
    double monsterToExit = calculateDistance(position, exitPosition);
    double playerToExit = calculateDistance(playerPosition, exitPosition);
    
    std::vector<int> targetPosition;
    
    // Strategic decision: Attack or Block?
    if (monsterToExit < playerToExit) {
        // Monster is closer to exit - CHASE player (attack mode)
        targetPosition = playerPosition;
        std::cout << "  Monster in ATTACK MODE - chasing player!" << std::endl;
    } else {
        // Player is closer to exit - BLOCK exit (defensive mode)
        targetPosition = exitPosition;
        std::cout << "  Monster in BLOCK MODE - moving to exit!" << std::endl;
    }
    
    // Calculate direction vector toward target
    std::vector<int> direction = {0, 0};
    
    // Horizontal direction
    if (targetPosition[0] > position[0]) {
        direction[0] = 1;   // Move right
    } else if (targetPosition[0] < position[0]) {
        direction[0] = -1;  // Move left
    }
    
    // Vertical direction
    if (targetPosition[1] > position[1]) {
        direction[1] = 1;   // Move up
    } else if (targetPosition[1] < position[1]) {
        direction[1] = -1;  // Move down
    }
    
    return direction;
}