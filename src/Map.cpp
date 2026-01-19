#include "Map.h"
#include <iostream>
#include <iomanip>

Map::Map(int numRows, int numCols)
    : rows(numRows), cols(numCols), exitPosition({numCols, numRows}) {
    // Initialize 2D vector with nullptr
    rooms.resize(numRows);
    for (int i = 0; i < numRows; i++) {
        rooms[i].resize(numCols, nullptr);
    }
}

Map::~Map() {
    // Delete all room objects (we own them - composition)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            delete rooms[i][j];
        }
    }
}

void Map::addRoom(Room* room) {
    if (room == nullptr) {
        return;
    }

    std::vector<int> pos = room->getPosition();
    int col = pos[0];
    int row = pos[1];

    // Convert from Cartesian (1-indexed) to array indices (0-indexed)
    int arrayRow = rows - row;      // Flip row (Cartesian y increases upward)
    int arrayCol = col - 1;          // Shift column

    if (arrayRow >= 0 && arrayRow < rows && arrayCol >= 0 && arrayCol < cols) {
        // Delete old room if exists
        if (rooms[arrayRow][arrayCol] != nullptr) {
            delete rooms[arrayRow][arrayCol];
        }
        rooms[arrayRow][arrayCol] = room;
    } else {
        std::cerr << "Error: Cannot add room at invalid position [" 
                  << col << ", " << row << "]" << std::endl;
        delete room;
    }
}

Room* Map::getRoom(std::vector<int> pos) const {
    return getRoom(pos[0], pos[1]);
}

Room* Map::getRoom(int col, int row) const {
    // Convert from Cartesian (1-indexed) to array indices (0-indexed)
    int arrayRow = rows - row;
    int arrayCol = col - 1;

    if (arrayRow >= 0 && arrayRow < rows && arrayCol >= 0 && arrayCol < cols) {
        return rooms[arrayRow][arrayCol];
    }
    return nullptr;
}

std::vector<int> Map::getDimensions() const {
    return {cols, rows};
}

std::vector<int> Map::getExitPosition() const {
    return exitPosition;
}

void Map::setExitPosition(std::vector<int> pos) {
    exitPosition = pos;
}

bool Map::isValidPosition(std::vector<int> pos) const {
    int col = pos[0];
    int row = pos[1];
    
    // Cartesian coordinates: col and row both start at 1
    return (col >= 1 && col <= cols && row >= 1 && row <= rows);
}

void Map::display() const {
    std::cout << "\n=== CAVE MAP ===" << std::endl;
    std::cout << "Dimensions: " << cols << " x " << rows << std::endl;
    std::cout << "Exit at: [" << exitPosition[0] << ", " << exitPosition[1] << "]" << std::endl;
    
    // Display grid (top to bottom = high row to low row)
    for (int i = 0; i < rows; i++) {
        int cartesianRow = rows - i;  // Convert back to Cartesian
        std::cout << "Row " << std::setw(2) << cartesianRow << ": ";
        
        for (int j = 0; j < cols; j++) {
            if (rooms[i][j] != nullptr) {
                std::string type = rooms[i][j]->getType();
                if (type == "Normal") {
                    std::cout << "[ N ]";
                } else if (type == "Poison") {
                    std::cout << "[ P ]";
                } else if (type == "Trap") {
                    std::cout << "[ T ]";
                }
            } else {
                std::cout << "[   ]";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "       ";
    for (int j = 1; j <= cols; j++) {
        std::cout << "  " << j << "  ";
    }
    std::cout << std::endl;
}