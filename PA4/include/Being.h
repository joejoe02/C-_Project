#ifndef BEING_H
#define BEING_H

#include <string>

using namespace std;

class Being {
protected:
    int life;
    int strength;
    int intelligence;
    string name;

public:

    Being(int life, int strength, int intelligence, const string& name = "");

    virtual ~Being();
    virtual string getType() const { return "Being"; }

    virtual void printDetails() const;

    // Get the life of the being
    void setLife(int newLife);
    int getLife() const;

    // Get the strength of the being
    void setStrength(int newStrength);
    int getStrength() const;

    // Get the intelligence of the being
    void setIntelligence(int newIntelligence);
    int getIntelligence() const;

    // Get the name of the being
    void setName(const string& newName);
    string getName() const;

    

};

#endif // BEING_H