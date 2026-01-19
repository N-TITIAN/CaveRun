#ifndef POISONROOM_H
#define POISONROOM_H

#include "Room.h"

/**
 * PoisonRoom - applies poison status to player on visit
 * Demonstrates polymorphism through visit() method override
 */
class PoisonRoom : public Room {
public:
    // Constructor
    PoisonRoom(std::vector<int> pos);

    // Override visit to apply poison effect
    void visit(Player* player) override;

    // Override getType
    std::string getType() const override;
};

#endif // POISONROOM_H