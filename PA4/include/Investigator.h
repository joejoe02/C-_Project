#ifndef INVESTIGATOR_H
#define INVESTIGATOR_H

#include "Person.h"
using namespace std;

class Investigator : public Person {
private:
    int terror; // scale 0-3

public:
    // Constructor
    Investigator(const string& name, int life, int strength, int intelligence, const string& gender, int fear, int terror);

    // Destructor
    virtual ~Investigator();
    string getType() const override { return "Investigator";}

    // Methods for managing terror
    void setTerror(int newTerror);
    int getTerror() const;

    // Create an investigator
    static Investigator* createInvestigator();

    void printDetails() const override;
};

#endif // INVESTIGATOR_H
