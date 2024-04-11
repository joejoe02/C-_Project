// CombatMechanics.cpp
#include <cstdlib>
#include <ctime>
#include "GameEntities.h"
#include "ErrorCheck.h"

void CombatMechanics::performCombat(Being* attacker, Being* target, const Item& weapon) {
    
    // Calculate damage
    int damage = calculateDamage(attacker, target, weapon);

    cout << attacker->getName() << " attacks " << target->getName() << " with " << weapon.getName() << endl;

    // Apply the damage to the target
    target->takeDamage(damage);

    cout << "Result: " << target->getName() << "'s life: " << target->getLife() << endl;

    // Update the CSV file with the new life value of the target
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




    // cout << attacker->getName() << " attacks " << target->getName() << " with " << weapon.getName() << endl;
    // cout << "Result: " << target->getName() << "'s life: " << target->getLife() << endl;
}


int CombatMechanics::calculateDamage(Being* attacker, Being* target, const Item& weapon) {
    // Calculate the base damage
    int baseDamage = attacker->getStrength() + weapon.getEffectStrength();

    // Calculate the modified damage
    baseDamage -= target->getStrength() + (target->getIntelligence()) / 2;

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
