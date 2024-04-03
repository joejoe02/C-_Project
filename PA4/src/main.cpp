#include <iostream>
#include "GameEntities.h"
#include <vector>
#include "GameMenu.h"
#include <chrono>

using namespace std;

vector<Being*> characters;

int main(){
srand(static_cast<unsigned>(chrono::system_clock::to_time_t(chrono::system_clock::now())));
showMainMenu();
    return 0;

}