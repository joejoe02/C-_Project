// CombatMechanics.h

#ifndef COMBAT_MECHANICS_H
#define COMBAT_MECHANICS_H

#include "GameEntities.h" // Include necessary headers for game entities and items
#include "Items.h"
#include <vector>

class CombatMechanics {
public:
    // Function to handle combat between characters
    static void performCombat(Being* attacker, Being* target, const Item& weapon);
    static Item chooseWeapon(const vector<Item>& items);


private:
    static int calculateDamage(Being* attacker, Being* target, const Item& weapon);
    // static int calculateFinalDamage(int baseDamage, const Item& weapon, Being* target);
    // static int calculateModifiedDamage(int baseDamage, const Item& weapon, const Being* target);
    // static int calculateFinalDamageWithModifiers(int modifiedDamage, const Being* target);



};

#endif // COMBAT_MECHANICS_H

