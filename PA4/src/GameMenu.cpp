#include "GameMenu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <typeinfo>
#include <algorithm>
#include "updateCSV.h"
#include "ErrorCheck.h"
#include "Items.h"

using namespace std;

extern vector<Being*> characters;
extern vector<Item> items;

void loadCharactersFromPersonsCSV(const string& filename);
void loadCreaturesFromCSV(const string& filename);
void loadEldritchHorrorsFromCSV(const string& filename);
void loadAllCharacters();
void loadAllItems(const string& filename);


void loadAllItems(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file for reading: " << filename << endl;
        return;
    }

    string header;
    getline(file, header);

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, typeStr, description;
        int effectStrength, effectFear;

        getline(ss, name, ',');
        getline(ss, typeStr, ',');
        getline(ss, description, ',');
        ss >> effectStrength;
        ss.ignore(); // Ignore comma
        ss >> effectFear;

        ItemType type = stringToItemType(typeStr);

        items.push_back(Item(name, type, description, effectStrength, effectFear));
    }

    file.close();
};


void loadCharactersFromPersonsCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file for reading: " << filename << endl;
        return;
    }

    // Skip the first line (header)
    string header;
    getline(file, header);

    string line, temp;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, gender, isInvStr;
        int life, strength, intelligence, fear;
        bool isInvestigator = false;
        int terror = 0;

        getline(ss, name, ',');
        ss >> life;
        ss.ignore(); // Ignore comma
        ss >> strength;
        ss.ignore(); // Ignore comma
        ss >> intelligence;
        ss.ignore(); // Ignore comma
        getline(ss, gender, ',');
        ss >> fear;
        ss.ignore(); // Ignore comma if it exists before IsInvestigator

        // Now check for the optional IsInvestigator field
        if (getline(ss, isInvStr, ',')) {
            // Remove potential whitespace and convert to lowercase for comparison
            isInvStr.erase(remove_if(isInvStr.begin(), isInvStr.end(), ::isspace), isInvStr.end());
            transform(isInvStr.begin(), isInvStr.end(), isInvStr.begin(), ::tolower);

            if (isInvStr == "true") {
                isInvestigator = true;
                // Only attempt to read terror if isInvestigator is true
                if (ss >> terror) {
                    // Successfully read terror
                }
            }
        }

        // Create Person or Investigator based on isInvestigator value
        if (isInvestigator) {
            characters.push_back(new Investigator(name, life, strength, intelligence, gender, fear, terror));
        } else {
            characters.push_back(new Person(name, life, strength, intelligence, gender, fear));
        }
    }

    file.close();
}

void loadCreaturesFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file for reading: " << filename << endl;
        return;
    }

    // Skip the header line
    string header;
    getline(file, header);

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        int life, strength, intelligence, disquiet;
        bool unnatural;

        getline(ss, name, ',');
        ss >> life;
        ss.ignore(); // Ignore comma
        ss >> strength;
        ss.ignore(); // Ignore comma
        ss >> intelligence;
        ss.ignore(); // Ignore comma
        ss >> unnatural;
        ss.ignore(); // Ignore comma
        ss >> disquiet;

        // Creating and adding the Creature object
        characters.push_back(new Creature("", name, life, strength, intelligence, unnatural, disquiet));


    }

    file.close();
}

void loadEldritchHorrorsFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file for reading: " << filename << endl;
        return;
    }

    // Skip the header line
    string header;
    getline(file, header);

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        int life, strength, intelligence, disquiet, traumatism;
        bool unnatural;

        getline(ss, name, ',');
        ss >> life;
        ss.ignore(); // Ignore comma
        ss >> strength;
        ss.ignore(); // Ignore comma
        ss >> intelligence;
        ss.ignore(); // Ignore comma
        ss >> unnatural;
        ss.ignore(); // Ignore comma
        ss >> disquiet;
        ss.ignore(); // Ignore comma
        ss >> traumatism;

        // Creating and adding the EldritchHorror object
        characters.push_back(new EldritchHorror(name, life, strength, intelligence, unnatural, disquiet, traumatism));
    }

    file.close();
}



void loadAllCharacters() {
    for (auto character : characters) {
        delete character;
    }

    characters.clear();

    loadCharactersFromPersonsCSV("data/Person.csv");    
    loadCreaturesFromCSV("data/Creature.csv");
    loadEldritchHorrorsFromCSV("data/EldritchHorror.csv");


}

void saveAllCharacters() {

    const string personHeader = "Name,Life,Strength,Intelligence,Gender,Fear,IsInvestigator,Terror";
    const string creatureHeader = "Name,Life,Strength,Intelligence,Unnatural,Disquiet";
    const string eldritchHorrorHeader = "Name,Life,Strength,Intelligence,Unnatural,Disquiet,Traumatism";
    // Open files for each character type in truncate mode to overwrite existing content
    ofstream personsFile("data/Person.csv",ios::out | ios::trunc);
    ofstream eldritchHorrorsFile("data/EldritchHorror.csv",ios::out | ios::trunc);
    ofstream creaturesFile("data/Creature.csv",ios::out | ios::trunc);

    if (!personsFile || !creaturesFile || !eldritchHorrorsFile) {
        cerr << "Failed to open one or more files for writing." << endl;
        return;
    }

    // Write the header line for each file
    personsFile << personHeader << "\n";
    creaturesFile << creatureHeader << "\n";
    eldritchHorrorsFile << eldritchHorrorHeader << "\n";

    for (const auto& character : characters) {
    if (const auto inv = dynamic_cast<Investigator*>(character)) {
        // Save as Investigator if the dynamic cast succeeds
        personsFile << inv->toCSV() << "\n";
    } else if (const auto p = dynamic_cast<Person*>(character)) {
        // Save as Person if it's not an Investigator
        personsFile << p->toCSV() << "\n";
    } else if (const auto eh = dynamic_cast<EldritchHorror*>(character)) {
        // Save eldritch horrors
        cout << "Saving Eldritch Horror: " << eh->getName() << endl;
        eldritchHorrorsFile << eh->toCSV() << "\n";
    } else if (const auto c = dynamic_cast<Creature*>(character)) {
        // Save creatures
        creaturesFile << c->toCSV() << "\n";
    }
}

    // Close the files
    personsFile.close();
    creaturesFile.close();
    eldritchHorrorsFile.close();


    cout << "All characters saved successfully." << endl;
}


void printAllCharacterDetails() {
    for (const auto& character : characters) {
        character->printDetails();
    }
}

void startCombat() {
    cout << "Starting combat...\n";
    CombatMechanics::performCombat(characters, items);
}


void showMainMenu() {
    int choice = 0;
    while (true) {
        cout << "\n=====================================\n"
             << "           MAIN MENU\n"
             << "=====================================\n"
             << "1. Create a character\n"
             << "2. Load all characters (if you have created a new character in session)\n"
             << "3. Print all character details\n"
             << "4. Print all items details\n"
             << "5. Battle!\n"
             << "6. Exit\n";

        choice = getNumericInput(1, 6, "Please enter your choice (1-6):");
        switch(choice) {
            case 1:
                createCharacter();
                break;
            case 2:
                loadAllCharacters();
                cout << "All characters loaded from CSV files.\n";
                break;
            case 3:
                printAllCharacterDetails();
                break;
            case 4:
                displayItems();
                break;
            case 5:
                startCombat();
                break;
            case 6:
                cout << "Exiting the program...\n";
                return; // Exit the program
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Example implementation for a function to create a character
void createCharacter() {
    cout << "\n=====================================\n"
         << "       CREATE A CHARACTER\n"
         << "=====================================\n"
         << "1. Create a person\n"
         << "2. Create an investigator\n"
         << "3. Create a creature\n"
         << "4. Create an eldritch horror\n"
         << "5. Back to main menu\n";
    
    int creationChoice = getNumericInput(1, 5, "Select the type of character to create (1-5): ");
    switch(creationChoice) {
        case 1:
            cout << "Creating a Person...\n";
            characters.push_back(Person::createPerson());
            break;
        case 2:
            cout << "Creating an Investigator...\n";
            characters.push_back(Investigator::createInvestigator());
            break;
        case 3:
            cout << "Creating a Creature...\n";
            characters.push_back(Creature::createCreature());
            break;
        case 4:
            cout << "Creating an Eldritch Horror...\n";
            characters.push_back(EldritchHorror::createEldritchHorror());
            break;
        case 5:
            cout << "Returning to main menu.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
    }
    if (creationChoice >= 1 && creationChoice <= 4) {
        cout << "Save new character? (y/n): ";
        char saveChoice;
        cin >> saveChoice;
        if (tolower(saveChoice) == 'y') {
            saveAllCharacters();
            cout << "Characters saved.\n";
        }
    }
}