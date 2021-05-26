// Kristen Tse
// Homework 06
// The following program uses the Warrior and Noble classes from homework
// 05, but adds a runaway function for warriors. This homework 
// demonstrates use of cyclic association, operator overloading, separate
// compilation, and namespace.

#include <iostream>
#include <string>
#include <vector>
#include "Warrior.h"
#include "Noble.h"
using namespace std;
using namespace WarriorCraft;

int main() {
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	cout << jim << endl;
	cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;

	cheetah.runaway();
	cout << art << endl;

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);
}
