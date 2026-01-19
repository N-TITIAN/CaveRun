#include "TrapRoom.h"
#include "Player.h"
#include <iostream>

TrapRoom::TrapRoom(std::vector<int> pos, int trapDamage)
    : Room(pos), damage(trapDamage) {
    // Initially looks like normal room
}

int TrapRoom::getDamage() const {
    return damage;
}

void TrapRoom::visit(Player* player) {
    if (!visited) {
        visited = true;
        color = "RED";
        label = "TRAP";

        std::cout << "\n*** TRAP ROOM at [" << position[0] << ", "
                  << position[1] << "] ***" << std::endl;
        std::cout << "The room turns RED - it's a trap!" << std::endl;
    } else {
        std::cout << "Entered known trap room at ["
                  << position[0] << ", " << position[1] << "]" << std::endl;
    }

    player->damage(damage);
    player->setRemainingMoves(0);  // End turn immediately
    std::cout << "TRAP triggered! Your turn ends immediately!" << std::endl;
}

std::string TrapRoom::getType() const {
    return "Trap";
}