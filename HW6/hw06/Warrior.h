#include <iostream>
#include <string>

#ifndef WARRIOR_H
#define WARRIOR_H 

namespace WarriorCraft {

	class Noble;

	class Warrior {
		friend std::ostream& operator<<(std::ostream& os, const Warrior& theWarrior);
	public:
		Warrior(const std::string& aName, const int aStrength);

		// Warrior runs away, meaning it gets removed from his employer's army
		// and becomes unemployed.
		void runaway();

		// Getters:
		Noble* getEmployer() const;
		std::string getName() const;
		int getStrength() const;

		// Setters:
		void setEmployer(Noble* noblePtr);
		void setStrength(int amount);

	private:
		std::string name;
		int strength;
		Noble* employer;
	};
}
#endif