#include "Creature.h"
#include <iostream>
#include <cstdlib> // For rand()

Creature::Creature(const string& name, int life, int strength, int intelligence, bool unnatural, int disquiet) : 
    Being(life, strength, intelligence, name), unnatural(unnatural), disquiet(disquiet) {}

Creature::~Creature() {}

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
    string name;
    cout << "Enter the name of the creature: ";
    getline(cin, name);

    int life = rand() % 11; // Life (0-10)
    int strength = rand() % 11; // Strength (0-10)
    int intelligence = rand() % 11; // Intelligence (0-10)
    bool unnatural = rand() % 2; // 0 or 1
    int disquiet = rand() % 11; // Disquiet (0-10)

    return new Creature(name, life, strength, intelligence, unnatural, disquiet);
}

void Creature::printDetails() const {
    Being::printDetails(); // Call base class implementation

    // Add Creature-specific details
    cout << "Unnatural     : " << (unnatural ? "Yes" : "No") << "\n";
    cout << "Disquiet      : " << disquiet << "\n";
    cout << "----------------------------------------------------------\n";
}
