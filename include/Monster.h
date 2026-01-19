#ifndef MONSTER_H
#define MONSTER_H

#include "Character.h"

/**
 * Monster class - represents the AI-controlled adversary
 * Uses strategic AI: chases player or blocks exit based on distance calculations
 */
class Monster : public Character {
private:
    std::vector<int> playerPosition;    // Cached player position from sensing
    std::vector<int> exitPosition;      // Cached exit position from sensing

    // Helper methods
    double calculateDistance(std::vector<int> pos1, std::vector<int> pos2) const;

protected:
    // Implementation of pure virtual from Character
    std::vector<int> getDirection() override;

public:
    // Constructor
    Monster(std::vector<int> startPos);

    // Override Character methods
    void sense(Game& game) override;
};

#endif // MONSTER_H