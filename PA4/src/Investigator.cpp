#include "Investigator.h"
#include <iostream>
#include <cstdlib> // For rand()
#include "ErrorCheck.h"

Investigator::Investigator(const string& name, int life, int strength, int intelligence, const string& gender, int fear, int terror)
: Person(name, life, strength, intelligence, gender, fear), terror(terror) {}

Investigator::~Investigator() {}

void Investigator::setTerror(int newTerror) {
    terror = newTerror;
}

int Investigator::getTerror() const {
    return terror;
}

Investigator* Investigator::createInvestigator() {
    std::string name = getStringInput("Enter the name of the investigator: ");
    std::string gender = getStringInput("Enter the gender: ");
    int terror = getNumericInput(0, 3, "Enter the terror level (0-3): ");
    int life = rand() % 11;
    int strength = rand() % 11;
    int intelligence = rand() % 11;
    int fear = rand() % 11;

    return new Investigator(name, life, strength, intelligence, gender, fear, terror);
}

void Investigator::printDetails() const {
    Person::printDetails();
    cout << "Terror         : " << getTerror() << "\n";
    cout << "---------------------------------------------------------------\n"; // Footer
}
