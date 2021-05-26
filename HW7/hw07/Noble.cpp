// The implementation for Noble and its derived classes.

#include <iostream>
#include <string>
#include <vector>
#include "Noble.h"
#include "Protector.h"
using namespace std;
using namespace WarriorCraft;


// Noble Implementation
Noble::Noble(const string& aName) : name(aName), dead(false) {}
void Noble::battle(Noble& otherNoble) {
	cout << name << " battles " << otherNoble.name << endl;
	this->yell();
	otherNoble.yell();
	// If only this noble is dead:
	if (getIsDead() == true && otherNoble.getIsDead() == false) {
		cout << "He's dead " << otherNoble.name << endl;
		return;
	}
	// If only the other Noble is dead:
	else if (getIsDead() == false && otherNoble.getIsDead() == true) {
		cout << "He's dead " << name << endl;
		return;
	}
	// If both Nobles are dead:
	else if (getIsDead() == true && otherNoble.getIsDead() == true) {
		cout << "Oh, NO! They're both dead! Yuck!\n";
		return;
	}
	// Both Nobles are alive so we must determine their strengths. 
	// We can also create a placeholder for which noble is stronger
	// and which is weaker.
	double strongStrength = this->determineStrength();
	double weakStrength = otherNoble.determineStrength();

	// If both Nobles have the same strength, they both die and their
	// warriors/selves now have zero strength:
	if (strongStrength == weakStrength) {
		cout << "Mutual Annihilation: " << name << " and "
			<< otherNoble.name << " die at each other's hands\n";
		dead = true;
		otherNoble.dead = true;
		this->setStrength(0);
		otherNoble.setStrength(0);
	}

	// If there is only one winner:
	else {
		// Swap the stronger/weaker placeholders if strongerStrength is 
		// actually the weaker warrior. Also swap the strength variables.
		Noble* strongerPtr = this;
		Noble* weakerPtr = &otherNoble;
		if (strongStrength < weakStrength) {
			swap(strongerPtr, weakerPtr);
			swap(strongStrength, weakStrength);
		}
		cout << strongerPtr->name << " defeats " << weakerPtr->name << endl;
		double ratio = (strongStrength - weakStrength) / strongStrength;
		// Winner now has their strength reduced by the ratio of the winning 
		// person's/army's strength to the losing.
		strongerPtr->setStrength(ratio);
		weakerPtr->setStrength(0);
		weakerPtr->dead = true;
	}
}
// Getters
string Noble::getName() const { return name; }
bool Noble::getIsDead() const { return dead; }


// Lord Implementation
Lord::Lord(const string& aName) : Noble(aName) {}
bool Lord::hires(Protector& aProtector) {
	if (Noble::getIsDead() == false && aProtector.getEmployerPtr() == nullptr 
		&& aProtector.getStrength() != 0) {
		aProtector.setEmployer(*this);
		vecArmy.push_back(&aProtector);
		return true;
	}
	return false;
}
bool Lord::fires(Protector& aProtector) {
	if (Noble::getIsDead() == false) {
		removeFromArmy(aProtector);
		aProtector.setEmployer();
		return true;
	}
	return false;
}

void Lord::removeFromArmy(Protector& aProtector) {
	for (size_t i = 0; i < vecArmy.size(); i++) {
		if (vecArmy[i]->getName() == aProtector.getName()) {
			for (size_t j = i; j < vecArmy.size() - 1; j++) {
				swap(vecArmy[i], vecArmy[i + 1]);
			}
			vecArmy.pop_back();
			break;
		}
	}
}

double Lord::determineStrength() const {
	double sum = 0;
	for (Protector* protecPtr : vecArmy) {
		sum += protecPtr->getStrength();
	}
	return sum;
}
void Lord::setStrength(const int ratio) {
	for (Protector* protecPtr : vecArmy) {
		protecPtr->setStrength(protecPtr->getStrength() * ratio);
	}
}
void Lord::yell() const {
	for (const Protector* protecPtr : vecArmy) {
		if (protecPtr->getStrength() != 0) {
			protecPtr->yell();
		}
	}
}


// PersonWithStrengthToFight Implementation
PersonWithStrengthToFight::PersonWithStrengthToFight(const string& aName, 
	const int aStrength) : Noble(aName), strength(aStrength) {}
double PersonWithStrengthToFight::determineStrength() const { 
	return strength; 
}
void PersonWithStrengthToFight::setStrength(const int ratio) { 
	strength *= ratio; 
}
void PersonWithStrengthToFight::yell() const {
	if (Noble::getIsDead() == false) {
		cout << "UGH!\n";
	}
}