#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Room.h"

/**
 * Map class - manages the 2D grid of rooms
 * Uses composition (owns all Room objects)
 * Provides boundary validation and room lookup
 */
class Map {
private:
    std::vector<std::vector<Room*>> rooms;  // 2D grid of room pointers
    int rows;                                // Number of rows
    int cols;                                // Number of columns
    std::vector<int> exitPosition;           // Exit room position

public:
    // Constructor and Destructor
    Map(int numRows, int numCols);
    ~Map();

    // Prevent copying (we own pointers)
    Map(const Map&) = delete;
    Map& operator=(const Map&) = delete;

    // Room management
    void addRoom(Room* room);
    Room* getRoom(std::vector<int> pos) const;
    Room* getRoom(int col, int row) const;

    // Map information
    std::vector<int> getDimensions() const;
    std::vector<int> getExitPosition() const;
    void setExitPosition(std::vector<int> pos);

    // Validation
    bool isValidPosition(std::vector<int> pos) const;

    // Display
    void display() const;
};

#endif // MAP_H