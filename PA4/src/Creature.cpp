#include "Creature.h"
#include <iostream>
#include <cstdlib> // For rand()
#include <map>
#include <fstream>
#include "ErrorCheck.h"

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

}


std::string Creature::generateName(const std::string& type) {
    int& count = nameCounts[type];
    count++;
    return type + " " + std::to_string(count);
}

void Creature::setName(const std::string& newName) {
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
    std::string type = getStringInput("Enter the type of the creature: ");
    int life = rand() % 11;
    int strength = rand() % 11;
    int intelligence = rand() % 11;
    bool unnatural = rand() % 2;  // 0 or 1
    int disquiet = rand() % 11;

    return new Creature(type, "", life, strength, intelligence, unnatural, disquiet);
}



void Creature::printDetails() const {
    Being::printDetails(); 

    // Add Creature-specific details
    cout << "Unnatural     : " << (unnatural ? "Yes" : "No") << "\n";
    cout << "Disquiet      : " << disquiet << "\n";
    cout << "----------------------------------------------------------\n";
}
