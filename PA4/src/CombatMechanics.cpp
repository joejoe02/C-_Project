// CombatMechanics.cpp
#include <cstdlib>
#include <ctime>

#include "CombatMechanics.h"

void CombatMechanics::performCombat(Being* attacker, Being* target, const Item& weapon) {
    
    int baseDamage = calculateDamage(attacker, target, weapon);


    target->takeDamage(baseDamage);
}

int CombatMechanics::calculateDamage(Being* attacker, Being* target, const Item& weapon) {
    // Calculate the base damage
    int baseDamage = attacker->getStrength() + weapon.getEffectStrength();

    // Calculate the modified damage
    baseDamage -= target->getStrength() + (target->getIntelligence()) / 2;

    baseDamage = max(baseDamage, 0); // Ensure that the damage is not negative

    return baseDamage;
}

