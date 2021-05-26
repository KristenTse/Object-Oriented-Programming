#include <iostream>
#include <string>
#include <vector>
#include "Warrior.h"

#ifndef NOBLE_H
#define NOBLE_H 

namespace WarriorCraft {

	// Create a Noble class that initializes a Noble's name and dead/alive status.
	// This class includes methods for hiring, firing, and battling Warriors. Note
	// that Nobles that are dead can't hire or fire warriors. The output operator 
	// was also overloaded.
	class Noble {
		friend std::ostream& operator<<(std::ostream& os, const Noble& theNoble);
	public:
		Noble(const std::string& aName);

		// Hires a warrior and appends the warrior pointer to the Army vector.
		// Returns true if this was successful, otherwise false.
		bool hire(Warrior& aWarrior);

		// Removes a warrior from the noble's army
		void removeFromArmy(Warrior& aWarrior);

		// Fires a warrior by looping through the Army vector and finding a
		// match. If a match is found, that index is swapped with the last 
		// index, then the last indexed item is popped off the vector.
		// Returns true if this was successful, otherwise false.
		bool fire(Warrior& aWarrior);

		// This method calculates the total strength of the Noble's army.
		double calcStrength(const Noble& aNoble);

		// This method battles the Nobles by using their armies and determines
		// the winner.
		void battle(Noble& otherNoble);

		// Getter
		std::string getName() const;

	private:
		std::string name;
		std::vector<Warrior*> vecArmy;
		bool dead;
	};
}
#endif