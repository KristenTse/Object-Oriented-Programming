// Kristen Tse
// Homework 04
// The following code creates a Warrior class and Noble class with methods for
// display and battle. This lab demonstrates the usage of class, association,
// and pointers.

#include <iostream>
#include <vector>
#include <string>
using namespace std;


// Create a Warrior class that initializes a Warrior's strength, name, and 
// employment status. Getters and setters are included for use in the Noble
// class. The output operator was also overloaded.
class Warrior {
	friend ostream& operator<<(ostream& os, const Warrior& theWarrior) {
		os << "\t" << theWarrior.name << ": " << theWarrior.strength << endl;
		return os;
	}
public:
	Warrior(const string& aName, const int aStrength)
		: name(aName), strength(aStrength), employed(false) {}

	// Getters:
	bool getEmployedStatus() const { return employed; }
	string getName() const { return name; }
	int getStrength() const { return strength; }

	// Setters:
	void setEmployedStatus(bool status) { employed = status; }
	void setStrength(int amount) { strength = amount; }

private:
	string name;
	int strength;
	bool employed;
};


// Create a Noble class that initializes a Noble's name and dead/alive status.
// This class includes mehtods for hiring, firing, and battling Warriors. Note
// that Nobles that are dead can't hire or fire warriors. The output operator 
// was also overloaded.
class Noble {
	friend ostream& operator<<(ostream& os, const Noble& theNoble) {
		os << theNoble.name << " has an army of " << theNoble.vecArmy.size() 
			<< endl;
		for (Warrior* warriorPtr : theNoble.vecArmy) {
			cout << *warriorPtr;
		}
		return os;
	}
public:
	Noble(const string& aName) : name(aName), dead(false) {}

	// Hires a warrior and appends the warrior pointer to the Army vector.
	// Returns true if this was successful, otherwise false.
	bool hire(Warrior& aWarrior) {
		if (!dead && !aWarrior.getEmployedStatus()) {
			aWarrior.setEmployedStatus(true);
			vecArmy.push_back(&aWarrior);
			return true;
		}
		return false;
	}

	// Fires a warrior by looping through the Army vector and finding a
	// match. If a match is found, that index is swapped with the last 
	// index, then the last indexed item is popped off the vector.
	// Returns true if this was successful, otherwise false.
	bool fire(Warrior& aWarrior) {
		if (!dead) {
			for (size_t i = 0; i < vecArmy.size(); i++) {
				if (vecArmy[i]->getName() == aWarrior.getName()) {
					cout << "You don't work for me anymore " << 
						aWarrior.getName() << "! -- " << name << ".\n";
					swap(vecArmy[i], vecArmy[vecArmy.size() - 1]);
					vecArmy.pop_back();
					return true;
				}
			}
		}
		return false;
	}

	// This method calculates the total strength of the Noble's army.
	double calcStrength(const Noble& aNoble) {
		double sum = 0;
		for (Warrior* warriorPtr : aNoble.vecArmy) {
			sum += warriorPtr->getStrength();
		}
		return sum;
	}

	// This method battles the Nobles by using their armies and determines
	// the winner.
	void battle(Noble& otherNoble) {
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
		Noble& stronger = *this;
		Noble& weaker = otherNoble;
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
private:
	string name;
	vector<Warrior*> vecArmy;
	bool dead;	
};


// The main function contains the test code given.
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

	cout << "==========\n"
		<< "Status before all battles, etc.\n";
	cout << jim << endl;
	cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;
	cout << "==========\n";

	art.fire(cheetah);
	cout << art << endl;
	
	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);
	
	cout << "==========\n"
		<< "Status after all battles, etc.\n";
	cout << jim << endl;
	cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;
	cout << "==========\n";
}
