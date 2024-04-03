#include "Investigator.h"
#include <iostream>
#include <cstdlib> // For rand()

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
    string name, gender;
    int terror = 0;
    cout << "Enter the name of the investigator: ";
   
getline(cin, name);

cout << "Enter the gender: ";
getline(cin, gender);

cout << "Enter the terror level (0-3): ";
cin >> terror;

int life = rand() % 11; // Life (0-10)
int strength = rand() % 11; // Strength (0-10)
int intelligence = rand() % 11; // Intelligence (0-10)
int fear = rand() % 11; // Fear (0-10)
// int terror = rand() % 4; // Terror (0-3)
cin.ignore();

return new Investigator(name, life, strength, intelligence, gender, fear, terror);
}

void Investigator::printDetails() const {
    Person::printDetails();
    cout << "Terror         : " << getTerror() << "\n";
    cout << "---------------------------------------------------------------\n"; // Footer
}
