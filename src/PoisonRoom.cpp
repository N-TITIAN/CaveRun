#include "PoisonRoom.h"
#include "Player.h"
#include <iostream>

PoisonRoom::PoisonRoom(std::vector<int> pos)
    : Room(pos) {
    // Initially looks like normal room
}

void PoisonRoom::visit(Player* player) {
    if (!visited) {
        // First visit - reveal the hazard
        visited = true;
        color = "GREEN";
        label = "POISON";
        
        std::cout << "\n*** POISON ROOM at [" << position[0] << ", " 
                  << position[1] << "] ***" << std::endl;
        std::cout << "The room turns GREEN - it's poisonous!" << std::endl;
    } else {
        std::cout << "Entered known poison room at [" 
                  << position[0] << ", " << position[1] << "]" << std::endl;
    }
    
    // Apply poison effect (every visit)
    player->poison();
}

std::string PoisonRoom::getType() const {
    return "Poison";
}