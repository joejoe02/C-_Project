// CombatMechanics.h

#ifndef COMBAT_MECHANICS_H
#define COMBAT_MECHANICS_H

#include "GameEntities.h" // Include necessary headers for game entities and items
#include "Items.h"
#include <vector>

class CombatMechanics {
public:
    static void performCombat(vector<Being*>& characters, vector<Item>& items);
    static Item chooseWeapon(const vector<Item>& items);
    static Being* chooseAttacker(const vector<Being*>& characters);
    static Being* chooseTarget(const vector<Being*>& characters, Being* attacker);
    static void updateCSVFiles(Being* target);


private:
    static int calculateDamage(Being* attacker, Being* target, const Item& weapon);


};

#endif // COMBAT_MECHANICS_H

