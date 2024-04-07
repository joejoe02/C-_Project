#include "Being.h"
#include <iostream>
using namespace std;

// Constructor
Being::Being(int life, int strength, int intelligence, const string& name) : life(life), strength(strength), intelligence(intelligence), name(name) {
}

// Destructor
Being::~Being() {
}


// Set the life of the being
void Being::setLife(int newLife) {
    life = newLife;
}

int Being::getLife() const {
    return life;
}


// Set the strength of the being
void Being::setStrength(int newStrength) {
    strength = newStrength;
}

int Being::getStrength() const {
    return strength;
}


// Set the intelligence of the being
void Being::setIntelligence(int newIntelligence) {
    intelligence = newIntelligence;
}

int Being::getIntelligence() const {
    return intelligence;
}

// Set the name of the being
void Being::setName(const string& newName) {
    name = newName;
}

string Being::getName() const {
    return name;
}

void Being::takeDamage(int damage) {
    if (damage > life) {
        life = 0;
    } else {
        life -= damage;
    }
}

void Being::printDetails() const {
    cout << "---------------------- Being Details ----------------------\n";
    cout << "Name          : " << name << "\n";
    cout << "Life          : " << life << "\n";
    cout << "Strength      : " << strength << "\n";
    cout << "Intelligence  : " << intelligence << "\n";
}