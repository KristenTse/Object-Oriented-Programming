#include <iostream>
#include <string>
#include "Warrior.h"
#include "Noble.h"
using namespace std;

namespace WarriorCraft {

	ostream& operator<<(ostream& os, const Warrior& theWarrior) {
		os << theWarrior.name << ": " << theWarrior.strength;
		return os;
	}

	Warrior::Warrior(const std::string& aName, const int aStrength)
		: name(aName), strength(aStrength), employer(nullptr) {}

	void Warrior::runaway() {
		cout << name << " flees in terror, abandoning his lord, " <<
			employer->getName() << endl;
		employer->removeFromArmy(*this);
		employer = nullptr;
	}

	Noble* Warrior::getEmployer() const { return employer; }
	string Warrior::getName() const { return name; }
	int Warrior::getStrength() const { return strength; }

	void Warrior::setEmployer(Noble* noblePtr) { employer = noblePtr; }
	void Warrior::setStrength(int amount) { strength = amount; }
}
