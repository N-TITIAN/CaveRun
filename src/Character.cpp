#include "Character.h"
#include "Room.h"
#include "Map.h"
#include <iostream>

Character::Character(std::vector<int> startPos, int maxMovesPerTurn,
                     std::string displayColor, char displayLabel)
    : position(startPos), currentRoom(nullptr), movesRemaining(maxMovesPerTurn),
      maxMoves(maxMovesPerTurn), color(displayColor), label(displayLabel) {
}

std::vector<int> Character::getPosition() const {
    return position;
}

Room* Character::getRoom() const {
    return currentRoom;
}

int Character::getMoves() const {
    return movesRemaining;
}

std::string Character::getColor() const {
    return color;
}

char Character::getLabel() const {
    return label;
}

void Character::setRoom(Room* room) {
    currentRoom = room;
}

void Character::resetMoves() {
    movesRemaining = maxMoves;
}

void Character::decrementMoves() {
    if (movesRemaining > 0) {
        movesRemaining--;
    }
}

void Character::move(Map& map) {
    if (movesRemaining <= 0) {
        return; // No moves left
    }

    // Get direction from subclass (Template Method pattern)
    std::vector<int> direction = getDirection();

    // Calculate new position
    std::vector<int> newPosition = {
        position[0] + direction[0],
        position[1] + direction[1]
    };

    // Validate position is within map bounds
    if (!map.isValidPosition(newPosition)) {
        std::cout << color << " " << label << ": Invalid move - out of bounds!" << std::endl;
        decrementMoves();
        return;
    }

    // Get the room at new position
    Room* newRoom = map.getRoom(newPosition);

    if (newRoom != nullptr) {
        // Update position and room
        position = newPosition;
        currentRoom = newRoom;

        std::cout << color << " " << label << " moved to ["
                  << position[0] << ", " << position[1] << "]" << std::endl;
    }

    decrementMoves();
}

void Character::update() {
    // Default: no update behavior
    // Subclasses can override
}