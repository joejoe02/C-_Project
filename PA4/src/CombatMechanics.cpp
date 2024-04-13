// CombatMechanics.cpp
#include <cstdlib>
#include <ctime>
#include "GameEntities.h"
#include "ErrorCheck.h"

using namespace std;
extern vector<Item> items;
extern vector<Being*> characters;

Being* CombatMechanics::chooseAttacker(const vector<Being*>& characters) {
    // Display available characters to the user
    cout << "Available characters:\n";
    for (size_t i = 0; i < characters.size(); ++i) {
        cout << i + 1 << ". " << characters[i]->getName() << " (Life: " << characters[i]->getLife() << ", Strength: " << characters[i]->getStrength() << ", Intelligence: " << characters[i]->getIntelligence() << ")\n";
    }

    // Ask the user to choose a character, providing a prompt with the valid range
    int choice = getNumericInput(1, characters.size(), "Choose an attacker (1-" + to_string(characters.size()) + "): ");
    return characters[choice - 1]; // Return the chosen character

}

Being* CombatMechanics::chooseTarget(const vector<Being*>& characters, Being* attacker) {
    // Display available characters to the user
    cout << "Available targets:\n";
    for (size_t i = 0; i < characters.size(); ++i) {
        if (characters[i] != attacker) {
            cout << i + 1 << ". " << characters[i]->getName() << " (Life: " << characters[i]->getLife() << ", Strength: " << characters[i]->getStrength() << ", Intelligence: " << characters[i]->getIntelligence() << ")\n";
        }
    }

    // Ask the user to choose a target, providing a prompt with the valid range
    int choice = getNumericInput(1, characters.size(), "Choose a target (1-" + to_string(characters.size()) + "): ");
    return characters[choice - 1]; // Return the chosen target
}



void CombatMechanics::performCombat(vector<Being*>& characters, vector<Item>& items) {
    Being* attacker = chooseAttacker(characters);
    Being* target = chooseTarget(characters, attacker);

    if (!attacker || !target || attacker == target) {
        cout << "Invalid attacker or target. Combat cannot proceed.\n";
        return;
    }

    cout << "Combat starts between " << attacker->getName() << " and " << target->getName() << "!\n";

    srand(time(nullptr)); // Seed the random number generator

    while (attacker->getLife() > 0 && target->getLife() > 0) {
        cout << attacker->getName() << "'s turn. Do you want to attack (1) or try to flee (2)? ";
        int choice;
        cin >> choice;

        // If the user tries to flee and fails he attacks
        if (choice == 2) {
            if (rand() % 100 < 40) { // 40% chance to successfully flee
                cout << attacker->getName() << " successfully fled the battle!\n";
                break; // End combat
            } else {
                cout << attacker->getName() << " failed to flee the battle!\n\n";
            }
        }

        Item weapon = chooseWeapon(items);
        if (weapon.getType() == ItemType::Weapon && weapon.getName() == "Mjolnir") {
            if (attacker->getStrength() < 8 || attacker->getIntelligence() < 7){
                cout << "You are not worthy to wield Mjolnir. Using default weapon.\n";
                weapon = Item("Fists", ItemType::Weapon, "Default weapon", 0, 0);
            }
        }
        int damage = calculateDamage(attacker, target, weapon);
        if (damage > target->getLife()) {
            damage = target->getLife();
        }
        target->takeDamage(damage);

        cout << attacker->getName() << " attacks " << target->getName()
             << " with " << weapon.getName() << " for " << damage << " damage.\n";
        cout << target->getName() << "'s life: " << target->getLife() << endl;

        updateCSVFiles(target);

        if (target->getLife() <= 0) {
            cout << target->getName() << " has been defeated!\n";
            break;
        }

        cout << "\nNow " << target->getName() << " is the attacker and " << attacker->getName() << " is the target.\n";
        swap(attacker, target); // Swap roles
        
        if (attacker->getLife() <= 0) {
            cout << attacker->getName() << " has been defeated!\n";
            break;
        }
    }
}



int CombatMechanics::calculateDamage(Being* attacker, Being* target, const Item& weapon) {

    // If target is being attacked by a weapon with fear effect, reduce target's intelligence
    if (weapon.getEffectFear() > 0) {
        if (weapon.getEffectFear() > target->getIntelligence()) { // Ensure that intelligence is not negative
            target->setIntelligence(0);
            cout << target->getName() << "'s intelligence reduced to 0 due to fear effect.\n";
        }
        target->setIntelligence(target->getIntelligence() - weapon.getEffectFear());
        cout << target->getName() << "'s intelligence reduced by " << weapon.getEffectFear() << " due to fear effect.\n";
    }

    // Calculate the base damage
    int baseDamage = (attacker->getStrength() / 2) + weapon.getEffectStrength(); // Use attacker strength as a factor in the damage

    // A chance for attacker to land a critical hit based on their intelligence
    int criticalChance = attacker->getIntelligence() / 4;
    if (rand() % 100 < criticalChance) {
        cout << attacker->getName() << " landed a critical hit!\n";
        baseDamage *= 1.5; // 50% increase in damage if attacked lands a critical hit
    }

    // A chance for target to block the attack based on their strength but reduce the chance based off the targets fear
    int blockChance = target->getStrength() - weapon.getEffectFear();
    if (rand() % 100 < blockChance) {
        cout << target->getName() << " blocked the attack!\n";
        baseDamage = 0; // No damage if the attack is blocked
    }

    // If target is attacked by Mjolnir he is stunned and cannot attack
    if (weapon.getName() == "Mjolnir") {
        cout << target->getName() << " is stunned by Mjolnir and cannot attack!\n";
    }

    

    // Calculate the modified damage
    baseDamage -= target->getStrength() + (target->getIntelligence() / 3); 
    baseDamage = max(0, baseDamage); // Ensure that the damage is not negative

    return baseDamage;
}

Item CombatMechanics::chooseWeapon(const std::vector<Item>& items) {
    // Display available weapons to the user
    std::cout << "Available weapons:\n";
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << i + 1 << ". " << items[i].getName() << " (Effect strength: " << items[i].getEffectStrength() << ", Effect fear: " << items[i].getEffectFear() << ")\n";
    }

    if (items.empty()) {
        std::cout << "No weapons available. Using default weapon.\n";
        return Item("Fists", ItemType::Weapon, "Default weapon", 0, 0);
    }

    // Ask the user to choose a weapon, providing a prompt with the valid range
    int choice = getNumericInput(1, items.size(), "Choose a weapon (1-" + std::to_string(items.size()) + "): ");
    return items[choice - 1]; // Return the chosen weapon
}


void CombatMechanics::updateCSVFiles(Being* target) {
    if (auto person = dynamic_cast<Person*>(target)) {
        updatePersonCSV("data/Person.csv", person);
    }
    else if (auto creature = dynamic_cast<Creature*>(target)) {
        updateCreatureCSV("data/Creature.csv", creature);
    }
    else if (auto eldritchHorror = dynamic_cast<EldritchHorror*>(target)) {
        updateEldritchHorrorCSV("data/Eldritch_horror.csv", eldritchHorror);
    }
    else {
        cout << "Unknown target type. Unable to update CSV file.\n";
    }
}