#include "Person.h"
#include <iostream>
#include <cstdlib> // For rand()
#include <fstream>
#include "ErrorCheck.h"
#include "Items.h"

using namespace std;

// Person constructor implementation
Person::Person(const string& name, int life, int strength, int intelligence, const string& gender, int fear)
: Being(life, strength, intelligence, name), gender(gender), fear(fear) {
    // Constructor initializes the person with the provided attributes
}

// Destructor
Person::~Person() {
    // Destructor to handle any cleanup if necessary
}

string Person::getGender() const {
    return gender;
}

void Person::setGender(const string& newGender) {
    gender = newGender;
}

int Person::getFear() const {
    return fear;
}

void Person::setFear(int newFear) {
    fear = newFear;
}

// Static method to create a person with random attributes
Person* Person::createPerson() {
    string name = getStringInput("Enter the name of the person: ");
    string gender = getStringInput("Enter gender: ");
    int life = rand() % 11;  // Life (0-10)
    int strength = rand() % 11;  // Strength (0-10)
    int intelligence = rand() % 11;  // Intelligence (0-10)
    int fear = rand() % 11;  // Fear (0-10)

    return new Person(name, life, strength, intelligence, gender, fear);
}

void Person::addItem(const Item& item) {
    inventory[item.getType()].push_back(item);
}

bool Person::useItem(const std::string& itemName) {
    auto& items = inventory[ItemType::Potion];
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getName() == itemName && it->getType() == ItemType::Potion) {
            adjustHealth(it->getEffectStrength());  // Assuming adjustHealth modifies health
            items.erase(it);  // Remove the item after use
            cout << "Used " << itemName << ", health adjusted." << endl;
            return true;
        }
    }
    cout << "No potion named " << itemName << " found in inventory." << endl;
    return false;
}


void Person::adjustHealth(int amount) {
    this->health += amount;
    std::cout << "Health adjusted by " << amount << ". Current health: " << this->health << std::endl;
}


void Person::printDetails() const {
    cout << "----------------------- Person Details -----------------------\n";
    cout << "Name          : " << getName() << "\n";
    cout << "Life          : " << getLife() << "\n";
    cout << "Strength      : " << getStrength() << "\n";
    cout << "Intelligence  : " << getIntelligence() << "\n";
    cout << "Gender        : " << getGender() << "\n";
    cout << "Fear          : " << getFear() << "\n";
    cout << "---------------------------------------------------------------\n";
}
