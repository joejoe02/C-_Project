#include "Items.h"
#include <iostream>
#include <vector>


using namespace std;

Item::Item(const string& name, ItemType type, const string& description, int effectStrength, int effectFear)
    : name(name), type(type), description(description), effectStrength(effectStrength), effectFear(effectFear) {}

string Item::getName() const {
    return name;
}

ItemType Item::getType() const {
    return type;
}

string Item::getDescription() const {
    return description;
}

int Item::getEffectStrength() const {
    return effectStrength;
}

int Item::getEffectFear() const {
    return effectFear;
}

ItemType stringToItemType(const string& type) {
    if (type == "Weapon") {
        return ItemType::Weapon;
    } else if (type == "Spellbook") {
        return ItemType::Spellbook;
    } else if (type == "Potion") {
        return ItemType::Potion;
    } else {
        return ItemType::Undefined;
    }
}
extern vector<Item> items;

void displayItems() {
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