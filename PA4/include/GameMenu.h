#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <vector>
#include <string>
#include "GameEntities.h" // Includes Being, Person, Creature, etc.

extern std::vector<Being*> characters;
extern std::vector<Item> items;

void savePerson(const Person* person);
void saveInvestigator(const Investigator* investigator);
void saveCreature(const Creature* creature);
void saveEldritchHorror(const EldritchHorror* eldritchHorror);

void loadCharactersFromPersonsCSV(const std::string& filename);
void loadCreaturesFromCSV(const std::string& filename);
void loadEldritchHorrorsFromCSV(const std::string& filename);

void loadAllCharacters();
void showMainMenu();

void loadAllItems(const std::string& filename);
void displayItems();

static int getNumericInput(int min, int max);

#endif // GAME_MENU_H
