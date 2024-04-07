#ifndef CREATURE_H
#define CREATURE_H

#include "Being.h"
#include <string>
#include <map>

// Forward declaration to avoid circular dependencies, if necessary
class Being;

class Creature : public Being {
private:
    static std::map<std::string, int> nameCounts; // Tracks the number of each creature type
    bool unnatural; // Indicates if the creature is unnatural
    int disquiet; // Represents the disquiet of the creature

    // Helper function to generate a unique name for the creature
    std::string generateName(const std::string& type);

public:
    // Constructor with default parameters, allowing for optional specification of all attributes
    Creature(const std::string& type = "", const std::string& name = "", int life = 0, int strength = 0, int intelligence = 0, bool unnatural = false, int disquiet = 0);

    // Virtual destructor to allow for proper cleanup in derived classes
    virtual ~Creature();

    void takeDamage(int damage) override {
        life -= damage;
    };

    // Setters and getters for 'unnatural' and 'disquiet' attributes
    void setUnnatural(bool newUnnatural);
    bool getUnnatural() const;
    void setDisquiet(int newDisquiet);
    int getDisquiet() const;
    void setName(const std::string& newName);
    // Static method to create a creature; implementation might involve user input or other logic
    static Creature* createCreature();

    // Override to print details specific to `Creature`
    void printDetails() const override;

    // Additional creature-specific methods here...
};

#endif // CREATURE_H
