#include "Room.h"
#include "Player.h"
#include <iostream>

Room::Room(std::vector<int> pos)
    : position(pos), color("WHITE"), label(""), visited(false) {
}

std::vector<int> Room::getPosition() const {
    return position;
}

std::string Room::getColor() const {
    return color;
}

std::string Room::getLabel() const {
    return label;
}

bool Room::isVisited() const {
    return visited;
}

void Room::setColor(std::string newColor) {
    color = newColor;
}

void Room::setLabel(std::string newLabel) {
    label = newLabel;
}

void Room::visit(Player* player) {
    // Normal room does nothing to the player
    if (!visited) {
        visited = true;
        std::cout << "Entered a normal room at [" 
                  << position[0] << ", " << position[1] << "]" << std::endl;
    }
}

std::string Room::getType() const {
    return "Normal";
}