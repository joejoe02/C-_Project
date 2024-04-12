#include <iostream>
#include "GameEntities.h"
#include <vector>
#include "GameMenu.h"
#include <chrono>

using namespace std;

vector<Being*> characters;
vector<Item> items;

void initializeGame(){
    loadAllCharacters();
    loadAllItems("data/Items.csv");
}


int main(){
srand(static_cast<unsigned>(chrono::system_clock::to_time_t(chrono::system_clock::now())));
initializeGame();
showMainMenu();
    return 0;

}