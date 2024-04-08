To compile:
g++ -o game src/main.cpp src/Being.cpp src/Person.cpp src/Creature.cpp src/EldritchHorror.cpp src/Investigator.cpp src/GameMenu.cpp src/Items.cpp src/CombatMechanics.cpp src/updateCSV.cpp -IincludeTo run:
./game

When the user creates a character or multiple characters he has to load them into the file in the GameMenu
and then he can see the characters in the file.