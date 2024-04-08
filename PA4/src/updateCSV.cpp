#include "updateCSV.h"
#include "GameEntities.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void updatePersonCSV(const string& filename, const Person* person) {
    // Open the file in read mode to read all existing data
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Unable to open file for reading: " << filename << endl;
        return;
    }

    // Open a temporary file in write mode to write the updated data
    string tempFilename = filename + ".tmp";
    ofstream outFile(tempFilename);
    if (!outFile.is_open()) {
        cerr << "Unable to open temporary file for writing." << endl;
        inFile.close();  // Close the input file
        return;
    }

    string line;
    bool updated = false;  // Flag to track if the entry has been updated

    // Read each line from the input file and update if necessary
    while (getline(inFile, line)) {
        stringstream ss(line);
        string name;
        int life, strength, intelligence, fear;
        // Read the data from the line
        // Assuming CSV format: name,life,strength,intelligence,gender,fear,is_investigator,terror
        getline(ss, name, ',');
        ss >> life; ss.ignore();
        ss >> strength; ss.ignore();
        ss >> intelligence; ss.ignore();
        ss.ignore(); // Skip gender
        ss >> fear;

        // Check if the current line corresponds to the person being updated
        if (name == person->getName()) {
            // Update the data
            outFile << name << "," << person->getLife() << "," << person->getStrength() << ","
                    << person->getIntelligence() << "," << person->getGender() << "," << person->getFear();
            
            // Check if the person is an Investigator
            if (const Investigator* inv = dynamic_cast<const Investigator*>(person)) {
                outFile << ",true," << inv->getTerror() << "\n";
            } else {
                outFile << ",false,0\n"; // If not an Investigator, fill in default values
            }
            updated = true;  // Set the flag to true
        } else {
            // Write the original data to the temporary file
            outFile << line << endl;
        }
    }

    // If the entry was not found, add it at the end of the file
    if (!updated) {
        outFile << person->getName() << "," << person->getLife() << "," << person->getStrength() << ","
                << person->getIntelligence() << "," << person->getGender() << "," << person->getFear();

        // Check if the person is an Investigator
        if (const Investigator* inv = dynamic_cast<const Investigator*>(person)) {
            outFile << ",true," << inv->getTerror() << "\n";
        } else {
            outFile << ",false,0\n"; // If not an Investigator, fill in default values
        }
    }

    // Close both input and output files
    inFile.close();
    outFile.close();

    // Replace the original file with the temporary file
    remove(filename.c_str());  // Remove the original file
    rename(tempFilename.c_str(), filename.c_str());  // Rename the temporary file
}


void updateCreatureCSV(const string& filename, const Creature* creature) {
    // Open the file in read mode to read all existing data
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Unable to open file for reading: " << filename << endl;
        return;
    }

    // Open a temporary file in write mode to write the updated data
    string tempFilename = filename + ".tmp";
    ofstream outFile(tempFilename);
    if (!outFile.is_open()) {
        cerr << "Unable to open temporary file for writing." << endl;
        inFile.close();  // Close the input file
        return;
    }

    string line;
    bool updated = false;  // Flag to track if the entry has been updated

    // Read each line from the input file and update if necessary
    while (getline(inFile, line)) {
        stringstream ss(line);
        string name;
        int life, strength, intelligence, unnatural, disquiet;
        // Read the data from the line
        // Assuming CSV format: name,life,strength,intelligence,unnatural,disquiet
        getline(ss, name, ',');
        ss >> life; ss.ignore();
        ss >> strength; ss.ignore();
        ss >> intelligence; ss.ignore();
        ss >> unnatural; ss.ignore();
        // Assuming the last field is disquiet
        ss >> disquiet;

        // Check if the current line corresponds to the creature being updated
        if (name == creature->getName()) {
            // Update the data
            outFile << name << "," << creature->getLife() << "," << creature->getStrength() << ","
                    << creature->getIntelligence() << "," << creature->getUnnatural() << "," << creature->getDisquiet() << "\n";
            updated = true;  // Set the flag to true
        } else {
            // Write the original data to the temporary file
            outFile << line << endl;
        }
    }

    // If the entry was not found, add it at the end of the file
    if (!updated) {
        outFile << creature->getName() << "," << creature->getLife() << "," << creature->getStrength() << ","
                << creature->getIntelligence() << "," << creature->getUnnatural() << "," << creature->getDisquiet() << "\n";
    }

    // Close both input and output files
    inFile.close();
    outFile.close();

    // Replace the original file with the temporary file
    remove(filename.c_str());  // Remove the original file
    rename(tempFilename.c_str(), filename.c_str());  // Rename the temporary file
}

void updateEldritchHorrorCSV(const string& filename, const EldritchHorror* horror) {
    // Open the file in read mode to read all existing data
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Unable to open file for reading: " << filename << endl;
        return;
    }

    // Open a temporary file in write mode to write the updated data
    string tempFilename = filename + ".tmp";
    ofstream outFile(tempFilename);
    if (!outFile.is_open()) {
        cerr << "Unable to open temporary file for writing." << endl;
        inFile.close();  // Close the input file
        return;
    }

    string line;
    bool updated = false;  // Flag to track if the entry has been updated

    // Read each line from the input file and update if necessary
    while (getline(inFile, line)) {
        stringstream ss(line);
        string name;
        int life, strength, intelligence, unnatural, disquiet, traumatism;
        // Read the data from the line
        // Assuming CSV format: name,life,strength,intelligence,unnatural,disquiet,traumatism
        getline(ss, name, ',');
        ss >> life; ss.ignore();
        ss >> strength; ss.ignore();
        ss >> intelligence; ss.ignore();
        ss >> unnatural; ss.ignore();
        ss >> disquiet; ss.ignore();
        // Assuming the last field is traumatism
        ss >> traumatism;

        // Check if the current line corresponds to the horror being updated
        if (name == horror->getName()) {
            // Update the data
            outFile << name << "," << horror->getLife() << "," << horror->getStrength() << ","
                    << horror->getIntelligence() << "," << horror->getUnnatural() << "," << horror->getDisquiet() << ","
                    << horror->getTraumatism() << "\n";
            updated = true;  // Set the flag to true
        } else {
            // Write the original data to the temporary file
            outFile << line << endl;
        }
    }

    // If the entry was not found, add it at the end of the file
    if (!updated) {
        outFile << horror->getName() << "," << horror->getLife() << "," << horror->getStrength() << ","
                << horror->getIntelligence() << "," << horror->getUnnatural() << "," << horror->getDisquiet() << ","
                << horror->getTraumatism() << "\n";
    }

    // Close both input and output files
    inFile.close();
    outFile.close();

    // Replace the original file with the temporary file
    remove(filename.c_str());  // Remove the original file
    rename(tempFilename.c_str(), filename.c_str());  // Rename the temporary file
}
