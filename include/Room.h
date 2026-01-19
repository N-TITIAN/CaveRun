#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <string>

// Forward declaration
class Player;

/**
 * Base Room class
 * Uses polymorphism for different room types (Normal, Poison, Trap)
 */
class Room {
protected:
    std::vector<int> position;    // Position in grid [col, row]
    std::string color;            // Display color
    std::string label;            // Text label
    bool visited;                 // Has player visited this room?

public:
    // Constructor
    Room(std::vector<int> pos);

    // Virtual destructor
    virtual ~Room() = default;

    // Getters
    std::vector<int> getPosition() const;
    std::string getColor() const;
    std::string getLabel() const;
    bool isVisited() const;

    // Setters
    void setColor(std::string newColor);
    void setLabel(std::string newLabel);

    // Virtual methods for polymorphism
    virtual void visit(Player* player);
    virtual std::string getType() const;
};

#endif // ROOM_H