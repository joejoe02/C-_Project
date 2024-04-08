#ifndef UPDATE_CSV_H
#define UPDATE_CSV_H

#include "GameEntities.h"

void updatePersonCSV(const string& filename, const Person* person);
void updateCreatureCSV(const string& filename, const Creature* creature);
void updateEldritchHorrorCSV(const string& filename, const EldritchHorror* eldritchHorror);

#endif // UPDATE_CSV_H
