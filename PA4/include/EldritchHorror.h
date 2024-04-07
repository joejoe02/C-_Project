#ifndef ELDRITCHHORROR_H
#define ELDRITCHHORROR_H

#include "Creature.h"
using namespace std;

class EldritchHorror : public Creature {
private:
    int traumatism;

public:
    EldritchHorror(const string& name, int life, int strength, int intelligence, bool unnatural, int disquiet, int traumatism);
    virtual ~EldritchHorror(); // Just declare the destructor

    string getType() const override { return "EldritchHorror";}
    void setTraumatism(int newTraumatism);
    int getTraumatism() const;

    void takeDamage(int damage) override {
        life -= damage;
    };

    // Create an eldritch horror
    static EldritchHorror* createEldritchHorror();

    void printDetails() const override;
};

#endif // ELDRITCHHORROR_H
