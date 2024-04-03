#ifndef CREATURE_H
#define CREATURE_H

#include "Being.h"
using namespace std;

class Creature : public Being {
protected:
    bool unnatural; // True if the creature is unnatural, false otherwise
    int disquiet; // The disquiet of the creature

public:

    // Constructor
    Creature(const string& name, int life, int strength, int intelligence, bool unnatural, int disquiet);

    // Destructor
    virtual ~Creature();
    string getType() const override { return "Creature";}

    // Get the unnatural attribute of the creature
    void setUnnatural(bool newUnnatural);
    bool getUnnatural() const;

    // Get the disquiet of the creature
    void setDisquiet(int newDisquiet);
    int getDisquiet() const;

    // Create a creature
    static Creature* createCreature();

    void printDetails() const override;

};




#endif // CREATURE_H