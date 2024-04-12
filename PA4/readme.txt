Use this command to compile the program:
g++ -o game src/main.cpp src/Being.cpp src/Person.cpp src/Creature.cpp src/EldritchHorror.cpp src/Investigator.cpp src/GameMenu.cpp src/Items.cpp src/CombatMechanics.cpp src/updateCSV.cpp src/ErrorCheck.cpp -Iinclude

After compiling, run the program with this command:
./game.exe

Welcome!
This program allows users to create, manage and engage in turn-based combat with other beings, including Investigators, Persons, Creatures and Eldritch Horrors.
Here's how the program works:

Character Creation:
- Users can choose to create four types of characters: Investigators, Persons, Creatures and Eldritch Horrors.
- When creating an Investigator, users provide a name, gender and terror level, while other attributes are randomized from the Person class.
- For Persons, users provide a name and gender and the program randomizes the rest of the attributes.
- For Creatures and Eldritch Horrors, users provide a name and the program randomizes the rest of the attributes.

Saving and loading characters:
- After creating a character, users have the option to save the character to the corresponding CSV file.
- Users must load all characters to include newly created characters in the printing and combat.
- Items are preloaded and do not need loading.

Printing characters:
- Users can choose to print all character details, which will print out all characters in the game including their attributes.

Turn-based combat:
- During combat, users can choose the character they want to attack and the character they want to attack with.
- The user then chooses an item to attack with, and the program calculates damage based on the attacker's attributes, the target's attributes and the selected weapon's effects.
- The program then prints out the results of the attack, including the damage dealt and the target's remaining health and updates the CSV files to reflect the current statistics of characters in battle.
- Items can vary from weapons, spells and potions, each with different effects and damage values.
- Based off the attacker's attributes he can use OP weapons which are able to stun the target for one turn.
- The combat system also calculates likelyhood of hitting a critical hit and the target's likelyhood of blocking the attack.
- The user can also choose to flee from combat, which will end the combat and return the user to the main menu, but it only has a 40% chance of success and if it fails the attacker forfeits their turn.
- The battle ends when wither the attacker's or the target's health reaches 0.