#pragma once
#include <string>
#include <iostream>

using namespace std;

enum class ItemType {
    Weapon,
    Spellbook,
    Potion,
    Undefined
};

class Item {
public:
    Item(const string& name, ItemType type, const string& description, int effectStrength, int effectFear);
    
    string getName() const;
    ItemType getType() const;
    string getDescription() const;
    int getEffectStrength() const;
    int getEffectFear() const;

private:
    string name;
    ItemType type;
    string description;
    int effectStrength;
    int effectFear;
};

ItemType stringToItemType(const string& type);