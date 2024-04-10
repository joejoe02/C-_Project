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

using namespace std;

extern vector<Being*> characters;
vector<Item> items;

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

        cout << "Loading character/Investigator..." << endl;
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
        cout << "Loading creature from line: " << line << endl;
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
        cout << "Loading Eldritch Horror from line: " << line << endl;
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
    // Open files for each character type. Using append mode in case you want to add to existing files.
    ofstream personsFile("data/Person.csv", ios::app);
    ofstream creaturesFile("data/Creature.csv", ios::app);
    ofstream eldritchHorrorsFile("data/EldritchHorror.csv", ios::app);

    if (!personsFile || !creaturesFile || !eldritchHorrorsFile) {
        cerr << "Failed to open one or more files for writing." << endl;
        return;
    }

    for (const auto& character : characters) {
        if (const auto p = dynamic_cast<Person*>(character)) {
            // Save both Person and Investigator in the same file, but add an extra field for Investigators
            personsFile << p->getName() << "," << p->getLife() << "," << p->getStrength() << ","
                        << p->getIntelligence() << "," << p->getGender() << "," << p->getFear();
            if (const auto inv = dynamic_cast<Investigator*>(character)) {
                // Append Investigator-specific fields
                personsFile << ",true," << inv->getTerror();
            }
            personsFile << "\n"; // Newline to separate characters
        } else if (const auto eh = dynamic_cast<EldritchHorror*>(character)) {
            eldritchHorrorsFile << eh->getName() << "," << eh->getLife() << "," << eh->getStrength() << ","
                                << eh->getIntelligence() << "," << eh->getUnnatural() << "," << eh->getDisquiet()
                                << "," << eh->getTraumatism() << "\n";
                                cout << "Eldritch Horror saved successfully." << endl;
        } else if (const auto c = dynamic_cast<Creature*>(character)) {
            creaturesFile << c->getName() << "," << c->getLife() << "," << c->getStrength() << ","
                          << c->getIntelligence() << "," << c->getUnnatural() << "," << c->getDisquiet() << "\n";
                          cout << "Creature saved successfully." << endl;
        
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

void printAllItems() {
    cout << "Items\n";
    cout << "---------------------------------------------------------------\n"; // Header
    for (const Item& item : items) {
        cout << "Name           : " << item.getName() << "\n";
        cout << "Type           : " << static_cast<int>(item.getType()) << "\n";
        cout << "Description    : " << item.getDescription() << "\n";
        cout << "Effect Strength: " << item.getEffectStrength() << "\n";
        cout << "Effect Fear    : " << item.getEffectFear() << "\n";
        cout << "---------------------------------------------------------------\n"; // Separator
    }

}

void initiateCombat() {
    cout << "Initiating combat...\n";

    // Display the list of characters with numbers
    cout << "Available characters:\n";
    for (size_t i = 0; i < characters.size(); ++i) {
        cout << i + 1 << ". " << characters[i]->getName() << endl;
    }

    // Select the attacker
    cout << "Select the attacker (enter the corresponding number): ";
    int attackerIndex;
    cin >> attackerIndex;
    cin.ignore(); // Ignore newline character
    if (attackerIndex < 1 || attackerIndex > characters.size()) {
        cout << "Invalid attacker selection.\n";
        return;
    }
    Being* attacker = characters[attackerIndex - 1];

    // Select the target
    cout << "Select the target (enter the corresponding number): ";
    int targetIndex;
    cin >> targetIndex;
    cin.ignore(); // Ignore newline character
    if (targetIndex < 1 || targetIndex > characters.size() || targetIndex == attackerIndex) {
        cout << "Invalid target selection.\n";
        return;
    }
    Being* target = characters[targetIndex - 1];

    // Display attacker and target details
    cout << "Attacker: " << attacker->getType() << " " << attacker->getName() << "\n" << endl;
    cout << "Target: " << target->getName() << " (Life: " << target->getLife() << "\n";
    
    // Check if the attacker is a Person and display fear
    if (auto person = dynamic_cast<Person*>(attacker)) {
        cout << ", Fear: " << person->getFear();
    }
    cout << ")\n";

    // Choose a weapon (you can implement this part if needed)
    Item weapon = CombatMechanics::chooseWeapon(items);

    // Perform combat
    CombatMechanics::performCombat(attacker, target, weapon);
}

void showMainMenu() {
    int choice = 0;
    while (true) {
        cout << "=====================================\n";
        cout << "           MAIN MENU\n";
        cout << "=====================================\n";
        cout << "1. Create a character\n";
        cout << "2. Save characters to a file\n";
        cout << "3. Load characters from a file\n";
        cout << "4. Print all character details\n";
        cout << "5. Print all Items details\n"; // Added this option to the menu
        cout << "6. Attack\n"; // Added this option to the menu
        cout << "7. Exit\n";
        cout << "\nPlease, select an option (1-6): ";
        int choice = getNumericInput(1, 7, "Please, select an option (1-7): ");

        switch(choice) {
            case 1: {
                cout << "\n=====================================\n";
                cout << "       CREATE A CHARACTER\n";
                cout << "=====================================\n";
                cout << "1. Create a person\n";
                cout << "2. Create an investigator\n";
                cout << "3. Create a creature\n";
                cout << "4. Create an eldritch horror\n";
                cout << "5. Back to main menu\n";
                cout << "\nSelect the type of character to create (1-5): ";
                int creationChoice = getNumericInput(1, 5, "Select the type of character to create (1-5): ");

                switch(creationChoice) {
                    case 1: {
                        cout << "Creating a Person...\n";
                        Person* newPerson = Person::createPerson();
                        characters.push_back(newPerson);
                        break;
                    }
                    case 2: {
                        cout << "Creating an Investigator...\n";
                        Investigator* newInvestigator = Investigator::createInvestigator();
                        characters.push_back(newInvestigator);
                        break;
                    }
                    case 3: {
                        cout << "Creating a Creature...\n";
                        Creature* newCreature = Creature::createCreature();
                        characters.push_back(newCreature);
                        break;
                    }
                    case 4: {
                        cout << "Creating an Eldritch Horror...\n";
                        EldritchHorror* newHorror = EldritchHorror::createEldritchHorror();
                        characters.push_back(newHorror);
                        break;
                    }
                    case 5:
                        break; // Go back to main menu
                    default:
                        cout << "Invalid choice. Please try again.\n";
                }
                break;
            }
            case 2:
                saveAllCharacters();
                break;
            case 3:
                loadAllCharacters();
                cout << "All characters loaded from CSV files.\n";
                break;
            case 4:
                printAllCharacterDetails();
                break; 
            case 5:
                loadAllItems("data/Items.csv");
                printAllItems();
                break;
            case 6:
                initiateCombat();
                break;
            case 7:
                cout << "Exiting the program...\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}