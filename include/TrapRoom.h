#ifndef TRAPROOM_H
#define TRAPROOM_H

#include "Room.h"

/**
 * TrapRoom - damages player and ends their turn immediately
 * Demonstrates polymorphism through visit() method override
 */
class TrapRoom : public Room {
private:
    int damage;    // Amount of damage trap inflicts

public:
    // Constructor
    TrapRoom(std::vector<int> pos, int trapDamage);

    // Getter
    int getDamage() const;

    // Override visit to apply trap effect
    void visit(Player* player) override;

    // Override getType
    std::string getType() const override;
};

#endif // TRAPROOM_H