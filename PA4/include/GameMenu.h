#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <vector>
#include <string>
#include "GameEntities.h" // Includes Being, Person, Creature, etc.

using namespace std;


extern vector<Being*> characters;
extern vector<Item> items;


void loadCharactersFromPersonsCSV(const string& filename);
void loadCreaturesFromCSV(const string& filename);
void loadEldritchHorrorsFromCSV(const string& filename);

void loadAllCharacters();
void showMainMenu();
void createCharacter();
void loadAllItems(const string& filename);
void displayItems();

static int getNumericInput(int min, int max);

#endif // GAME_MENU_H
