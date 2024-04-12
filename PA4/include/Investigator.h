#ifndef INVESTIGATOR_H
#define INVESTIGATOR_H

#include "Person.h"
#include <sstream>
using namespace std;

class Investigator : public Person {
private:
    int terror; 

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

    string toCSV() const {
        stringstream ss;
        ss << Person::toCSV() << "," << "true" << "," << terror;
        return ss.str();
    }
};

#endif // INVESTIGATOR_H
