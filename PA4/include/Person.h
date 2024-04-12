#ifndef PERSON_H
#define PERSON_H

#include "Being.h"
#include "items.h"
#include <vector>
#include <map>
using namespace std;

class Person : public Being {
private:
    std::map<ItemType, std::vector<Item>> inventory;  
    int health;
protected:
    string gender;
    int fear;

public:
    Person(const string& name, int life, int strength, int intelligence, const string& gender, int fear);
    virtual ~Person(); // Just declare the destructor

    string getType() const override { return "Person";}

    void takeDamage(int damage) override {
        if (damage > life)
            life = 0;
        else
            life -= damage;
    };

    void setGender(const string& newGender);
    string getGender() const;
    void setFear(int newFear);
    int getFear() const;
    // Create a person
    static Person* createPerson(); 
    void addItem(const Item& item);
    bool useItem(const std::string& itemName);
    void adjustHealth(int amount);
    void printDetails() const override;  

};

#endif // PERSON_H
