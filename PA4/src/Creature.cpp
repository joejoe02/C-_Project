#include "Creature.h"
#include <iostream>
#include <cstdlib> // For rand()
#include <map>
#include <fstream>

// Initialize the static nameCounts map
std::map<std::string, int> Creature::nameCounts;

Creature::Creature(const std::string& type, const std::string& name, int life, int strength, int intelligence, bool unnatural, int disquiet) 
: Being(life, strength, intelligence), unnatural(unnatural), disquiet(disquiet) {
    if (name.empty()) {
        this->name = generateName(type);  // Use generateName if no name is provided
    } else {
        this->name = name;  // Use the provided name
        nameCounts[type]++;  // Still increment the count for the type
    }
}

Creature::~Creature() {
    // Any cleanup code specific to Creature would go here.
    // If there's no specific cleanup needed, this can be left empty.
}


std::string Creature::generateName(const std::string& type) {
    int& count = nameCounts[type];
    count++;
    return type + " " + std::to_string(count);
}

void Creature::setName(const std::string& newName) {
    // Implementation, assuming 'name' is a member variable of 'Being' or 'Creature'
    this->name = newName;
}

void Creature::setUnnatural(bool newUnnatural) {
    unnatural = newUnnatural;
}

bool Creature::getUnnatural() const {
    return unnatural;
}

void Creature::setDisquiet(int newDisquiet) {
    disquiet = newDisquiet;
}

int Creature::getDisquiet() const {
    return disquiet;
}



Creature* Creature::createCreature() {
    std::string type; // This is now considered 'type' instead of 'name'
    std::cout << "Enter the type of the creature: ";
    std::getline(std::cin, type);

    int life = rand() % 11; // Life (0-10)
    int strength = rand() % 11; // Strength (0-10)
    int intelligence = rand() % 11; // Intelligence (0-10)
    bool unnatural = rand() % 2; // 0 or 1
    int disquiet = rand() % 11; // Disquiet (0-10)

    // Pass 'type' as the first argument, and leave 'name' as an empty string
    return new Creature(type, "", life, strength, intelligence, unnatural, disquiet);
}


void Creature::printDetails() const {
    Being::printDetails(); // Call base class implementation

    // Add Creature-specific details
    cout << "Unnatural     : " << (unnatural ? "Yes" : "No") << "\n";
    cout << "Disquiet      : " << disquiet << "\n";
    cout << "----------------------------------------------------------\n";
}
