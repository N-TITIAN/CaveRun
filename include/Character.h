#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include <string>

// Forward declarations
class Room;
class Game;
class Map;

/**
 * Abstract base class for all characters in the game (Player and Monster)
 * Implements Template Method pattern for movement
 */
class Character {
protected:
    std::vector<int> position;      // Current position [col, row] (Cartesian)
    Room* currentRoom;              // Pointer to current room
    int movesRemaining;             // Moves left in current turn
    int maxMoves;                   // Maximum moves per turn
    std::string color;              // Display color
    char label;                     // Single character label

    // Protected pure virtual method for subclasses to implement
    virtual std::vector<int> getDirection() = 0;

    // Protected helper
    void decrementMoves();

public:
    // Constructor
    Character(std::vector<int> startPos, int maxMovesPerTurn,
              std::string displayColor, char displayLabel);

    // Virtual destructor for proper cleanup
    virtual ~Character() = default;

    // Getters
    std::vector<int> getPosition() const;
    Room* getRoom() const;
    int getMoves() const;
    std::string getColor() const;
    char getLabel() const;

    // Setters
    void setRoom(Room* room);

    // Movement and turn management
    void resetMoves();

    // Pure virtual methods (must be implemented by subclasses)
    virtual void sense(Game& game) = 0;

    // Virtual methods (can be overridden)
    virtual void move(Map& map);
    virtual void update();
};

#endif // CHARACTER_H