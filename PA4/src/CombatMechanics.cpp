// CombatMechanics.cpp
#include <cstdlib>
#include <ctime>

#include "CombatMechanics.h"

void CombatMechanics::performCombat(Being* attacker, Being* target, const Item& weapon) {
    
    // Calculate damage
    int damage = calculateDamage(attacker, target, weapon);

    cout << attacker->getName() << " attacks " << target->getName() << " with " << weapon.getName() << endl;

    // Apply damage to the target
    target->takeDamage(damage);

    cout << "Result: " << target->getName() << "'s life: " << target->getLife() << endl;
}


int CombatMechanics::calculateDamage(Being* attacker, Being* target, const Item& weapon) {
    // Calculate the base damage
    int baseDamage = attacker->getStrength() + weapon.getEffectStrength();

    // Calculate the modified damage
    baseDamage -= target->getStrength() + (target->getIntelligence()) / 2;

    baseDamage = max(0, baseDamage); // Ensure that the damage is not negative

    return baseDamage;
}

Item CombatMechanics::chooseWeapon(const vector<Item>& items) {
     // Display available weapons to the user
    cout << "Available weapons:\n";
    for (size_t i = 0; i < items.size(); ++i) {
        cout << i + 1 << ". " << items[i].getName() << endl;
    }

    if (items.empty()) {
        cout << "No weapons available. Using default weapon.\n";
        return Item("Fists", ItemType::Weapon, "Default weapon", 0, 0);
    }

    // Prompt the user to choose a weapon
    int choice;
    cout << "Choose a weapon (1-" << items.size() << "): ";
    cin >> choice;

    // Validate the user's choice
    if (choice >= 1 && choice <= static_cast<int>(items.size())) {
        return items[choice - 1]; // Return the chosen weapon
    } else {
        cout << "Invalid choice. Using default weapon.\n";
        return items.front(); // Return the first weapon by default
    }
}