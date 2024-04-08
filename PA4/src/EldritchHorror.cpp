#include "EldritchHorror.h"
#include <iostream>
#include <cstdlib> // For rand()
#include <fstream>

EldritchHorror::EldritchHorror(const std::string& name, int life, int strength, int intelligence, bool unnatural, int disquiet, int traumatism)
: Creature("", name, life, strength, intelligence, unnatural, disquiet), traumatism(traumatism) {}

EldritchHorror::~EldritchHorror() {}

void EldritchHorror::setTraumatism(int newTraumatism) {
    traumatism = newTraumatism;
}

int EldritchHorror::getTraumatism() const {
    return traumatism;
}

// Creating an eldritch horror using random values
EldritchHorror* EldritchHorror::createEldritchHorror() {
    string name;
    cout << "Enter the name of the eldritch horror: ";
    getline(cin, name);

    int life = rand() % 11;
    int strength = rand() % 11;
    int intelligence = rand() % 11;
    int traumatism = rand() % 4; // 0-3

    return new EldritchHorror(name, life, strength, intelligence, true, 10, traumatism);
}

void EldritchHorror::printDetails() const {
    Creature::printDetails(); // Call to Creature's printDetails to print common details

    cout << "Traumatism     : " << getTraumatism() << "\n";
    cout << "---------------------------------------------------------------\n"; // Footer
}

