#include <iostream>
#include <string>
#include "Noble.h"
using namespace std;

namespace WarriorCraft {

	ostream& operator<<(ostream& os, const Noble& theNoble) {
		os << theNoble.name << " has an army of " << theNoble.vecArmy.size();
		for (Warrior* warriorPtr : theNoble.vecArmy) {
			cout << "\n\t" << *warriorPtr;
		}
		return os;
	}

	Noble::Noble(const string& aName) : name(aName), dead(false) {}

	bool Noble::hire(Warrior& aWarrior) {
		if (!dead && aWarrior.getEmployer() == nullptr) {
			aWarrior.setEmployer(this);
			vecArmy.push_back(&aWarrior);
			return true;
		}
		return false;
	}

	void Noble::removeFromArmy(Warrior& aWarrior) {
		for (size_t i = 0; i < vecArmy.size(); i++) {
			if (vecArmy[i]->getName() == aWarrior.getName()) {
				swap(vecArmy[i], vecArmy.back());
				vecArmy.pop_back();
				break;
			}
		}

	}

	bool Noble::fire(Warrior& aWarrior) {
		if (!dead) {
			cout << "You don't work for me anymore " <<
				aWarrior.getName() << "! -- " << name << ".\n";
			removeFromArmy(aWarrior);
			aWarrior.setEmployer(nullptr);
			return true;
		}
		return false;
	}

	double Noble::calcStrength(const Noble& aNoble) {
		double sum = 0;
		for (Warrior* warriorPtr : aNoble.vecArmy) {
			sum += warriorPtr->getStrength();
		}
		return sum;
	}

	void Noble::battle(Noble& otherNoble) {
		cout << name << " battles " << otherNoble.name << endl;
		// If only this noble is dead:
		if (dead == true && otherNoble.dead == false) {
			cout << "He's dead, " << otherNoble.name << endl;
			return;
		}
		// If only the other Noble is dead:
		else if (dead == false && otherNoble.dead == true) {
			cout << "He's dead, " << name << endl;
			return;
		}
		// If both Nobles are dead:
		else if (dead == true && otherNoble.dead == true) {
			cout << "Oh, NO! They're both dead! Yuck!\n";
			return;
		}
		// Both Nobles are alive so we must determine their strengths. 
		// We can also create a placeholder for which noble is stronger
		// and which is weaker.
		double strongStrength = calcStrength(*this);
		double weakStrength = calcStrength(otherNoble);

		// If both Nobles have the same strength, they both die and their
		// warriors now have zero strength:
		if (strongStrength == weakStrength) {
			cout << "Mutual Annihilation: " << name << " and "
				<< otherNoble.name << " die at each other's hands\n";
			dead = true;
			otherNoble.dead = true;
			for (Warrior* warriorPtr : vecArmy) {
				warriorPtr->setStrength(0);
			}
			for (Warrior* warriorPtr : otherNoble.vecArmy) {
				warriorPtr->setStrength(0);
			}
		}

		// If there is only one winner:
		else {
			// Swap the stronger/weaker placeholders if strongerStrength is 
			// actually the weaker warrior. Also swap the strength variables.
			Noble& stronger = *this;
			Noble& weaker = otherNoble;
			if (strongStrength < weakStrength) {
				swap(stronger, weaker);
				swap(strongStrength, weakStrength);
			}
			cout << stronger.name << " defeats " << weaker.name << endl;
			double ratio = (strongStrength - weakStrength) / strongStrength;
			// Warriors in the winning army now have their strength reduced by
			// the ratio of the winning army's strength to the losing army's
			// strength
			for (Warrior* warriorPtr : stronger.vecArmy) {
				warriorPtr->setStrength(warriorPtr->getStrength() * ratio);
			}
			// Warriors in the losing army now have their strength set to zero.
			weaker.dead = true;
			for (Warrior* warriorPtr : weaker.vecArmy) {
				warriorPtr->setStrength(0);
			}
		}
	}
	string Noble::getName() const { return name; }
}
