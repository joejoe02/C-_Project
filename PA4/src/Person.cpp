#include "Person.h"
#include <iostream>
#include <cstdlib> // For rand()

// Person constructor implementation
Person::Person(const string& name, int life, int strength, int intelligence, const string& gender, int fear)
: Being(life, strength, intelligence, name), gender(gender), fear(fear) {}

// Destructor
Person::~Person() {}

// Getter for gender
string Person::getGender() const {
    return gender;
}

void Person::setGender(const string& newGender) {}


// Getter for fear
int Person::getFear() const {
    return fear;
}

void Person::setFear(int newFear) {}

// Static method to create a person with random attributes
Person* Person::createPerson() {
    string name, gender;
    int life = rand() % 11; // Life (0-10)
    int strength = rand() % 11; // Strength (0-10)
    int intelligence = rand() % 11; // Intelligence (0-10)
    int fear = rand() % 11; // Fear (0-10)

    cout << "\nEnter the name of the person: ";
    getline(cin, name);

    cout << "\nEnter gender: ";
    getline(cin, gender);

    return new Person(name, life, strength, intelligence, gender, fear);
}



// Print the details of the person
void Person::printDetails() const {
    cout << "----------------------- Person Details -----------------------\n";
    cout << "Name          : " << getName() << "\n";
    cout << "Type          : " << getType() << "\n";
    cout << "Life          : " << getLife() << "\n";
    cout << "Strength      : " << getStrength() << "\n";
    cout << "Intelligence  : " << getIntelligence() << "\n";
    cout << "Gender        : " << getGender() << "\n";
    cout << "Fear          : " << getFear() << "\n";
    cout << "---------------------------------------------------------------\n";
}
