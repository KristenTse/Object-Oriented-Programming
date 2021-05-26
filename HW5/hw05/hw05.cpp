// Kristen Tse
// Homework 05
// The following program uses the Warrior class and Noble class to create
// Noble and Warrior objects on the heap. A file named "nobleWarriors.txt"
// is read in the main function, and the appropriate functions/methods
// are called based on the commands.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


// Create a Warrior class that initializes a Warrior's name, strength, and 
// employment status. This class includes getters for the name, strength,
// and employment status, and setters for the employment status and strength.
// The output operator was also overloaded.
class Warrior {
	friend ostream& operator<<(ostream& os, const Warrior& theWarrior) {
		os << theWarrior.name << ": " << theWarrior.strength << endl;
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
// This class includes methods for hiring, firing, and battling Warriors. Note
// that Nobles that are dead can't hire or fire warriors. The output operator 
// was also overloaded.
class Noble {
	friend ostream& operator<<(ostream& os, const Noble& theNoble) {
		os << theNoble.name << " has an army of " << theNoble.vecArmy.size() 
			<< endl;
		for (Warrior* warriorPtr : theNoble.vecArmy) {
			cout << "\t" << *warriorPtr;
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
					aWarrior.setEmployedStatus(false);
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
	string getName() const { return name; }
private:
	string name;
	vector<Warrior*> vecArmy;
	bool dead;	
};



int main() {
	// Open the file with the given name
	ifstream warriorFile("nobleWarriors.txt");

	// Create vectors to hold Noble and Warrior pointers
	vector<Noble*> vecNoblePtrs;
	vector<Warrior*> vecWarriorPtrs;

	// Read through the file and call the appropriate functions
	string command, nobleName, warriorName, nobleOne, nobleTwo;
	int strength;
	while (warriorFile >> command) {
		if (command == "Noble") {
			warriorFile >> nobleName;
			// First check if the noble already exists. If it does, display
			// an error message to the screen.
			for (Noble* noblePtr : vecNoblePtrs) {
				if (noblePtr->getName() == nobleName) {
					cerr << "A noble named " << nobleName 
						<< " already exists!";
					exit(1);
				}
			}
			// Otherwise, create a new noble object on the heap and add it's
			// pointer to vecNoblePtrs
			vecNoblePtrs.push_back(new Noble(nobleName));
		}
		else if (command == "Warrior") {
			warriorFile >> warriorName >> strength;
			// First check if the warrior already exists. If it does, 
			// display an error message to the screen
			for (Warrior* warriorPtr : vecWarriorPtrs) {
				if (warriorPtr->getName() == warriorName) {
					cerr << "A warrior named " << warriorName 
						<< " already exists!\n";
					exit(1);
				}
			}
			// Otherwise, create a new warrior on the heap and add it's
			// pointer to vecWarriorPtrs
			vecWarriorPtrs.push_back(new Warrior(warriorName, strength));
		}
		else if (command == "Hire") {
			warriorFile >> nobleName >> warriorName;
			bool warriorFound = false;
			// First check if the noble exists.
			for (Noble* noblePtr: vecNoblePtrs) {
				if (noblePtr->getName() == nobleName) {
					// If the noble exists, check if the warrior exists.
					// If it does, use the hire method to hire it.
					for (Warrior* warriorPtr : vecWarriorPtrs) {
						if (warriorPtr->getName() == warriorName) {
							noblePtr->hire(*warriorPtr);
							warriorFound = true;
							break;
						}
						// If the warrior does not exist, display an
						// error message.
						else if (warriorPtr == vecWarriorPtrs.back() &&
							warriorPtr->getName() != warriorName) {
							cerr << "This warrior doesn't exist!\n";
							exit(1);
						}
					}
				}
				else if (warriorFound) { break; }
				// If the noble doesn't exist, display an error message.
				else if (noblePtr == vecNoblePtrs.back() && 
					noblePtr->getName() != nobleName) {
					cerr << "This noble doesn't exist!\n";
					exit(1);
				}
			}
		}
		else if (command == "Fire") {
			warriorFile >> nobleName >> warriorName;
			bool warriorFound = false;
			// First check if the noble exists.
			for (Noble* noblePtr : vecNoblePtrs) {
				if (noblePtr->getName() == nobleName) {
					// If the noble exists, check if the warrior exists. 
					// If it does, use the fire method to fire it.
					for (Warrior* warriorPtr : vecWarriorPtrs) {
						if (warriorPtr->getName() == warriorName) {
							noblePtr->fire(*warriorPtr);
							warriorFound = true;
							break;
						}
						// If the warrior does not exist, display an
						// error message.
						else if (warriorPtr == vecWarriorPtrs.back() && 
							warriorPtr->getName() != warriorName) {
							cerr << warriorPtr->getName() << 
								" doesn't work for " << noblePtr->getName();
							exit(1);
						}
					}
				}
				else if (warriorFound) { break; }
				// If the noble does not exist, display an error 
				// message.
				else if (noblePtr == vecNoblePtrs.back() && 
					noblePtr->getName() != nobleName) {
					cerr << "This noble doesn't exist!\n";
					exit(1);
				}
			}
		}
		else if (command == "Battle") {
			warriorFile >> nobleOne >> nobleTwo;
			bool nobleTwoFound = false;
			// First check if the first noble exists
			for (Noble* noblePtrOne : vecNoblePtrs) {
				if (noblePtrOne->getName() == nobleOne) {
					// If the noble exists, check if the other noble exists.
					// If it does, use the battle method to fight the two.
					for (Noble* noblePtrTwo : vecNoblePtrs) {
						if (noblePtrTwo->getName() == nobleTwo) {
							noblePtrOne->battle(*noblePtrTwo);
							nobleTwoFound = true;
							break;
						}
						// If the other noble doesn't exist, display an 
						// error message.
						else if (noblePtrTwo == vecNoblePtrs.back() &&
							noblePtrTwo->getName() != warriorName) {
							cerr << noblePtrTwo->getName() 
								<< " doesn't exist!";
							exit(1);
						}
					}
				}
				else if (nobleTwoFound) { break; }
				// If the first noble doesn't exist, display an error
				// message.
				else if (noblePtrOne == vecNoblePtrs.back() &&
					noblePtrOne->getName() != warriorName) {
					cerr << noblePtrOne->getName()
						<< " doesn't exist!";
					exit(1);
				}
			}
		}
		else if (command == "Status") {
			cout << "Status\n======\n"
				<< "Nobles:\n";
			if (vecNoblePtrs.size() == 0) {
				cout << "NONE\n";
			}
			else {
				for (Noble* noblePtr : vecNoblePtrs) {
					cout << *noblePtr;
				}
			}
			int countEmployed = 0;
			cout << "Unemployed Warriors:\n";
			for (Warrior* warriorPtr : vecWarriorPtrs) {
				if (warriorPtr->getEmployedStatus() == false) {
					cout << *warriorPtr;
					countEmployed += 1;
				}
			}
			if (countEmployed == 0) {
				cout << "NONE\n";
			}
		}
		else if (command == "Clear") {
			// Delete each Noble pointer and Warrior pointer on the heap,
			// then clear both vectors.
			for (Noble* noblePtr : vecNoblePtrs) { delete noblePtr; }
			for (Warrior* warriorPtr : vecWarriorPtrs) { delete warriorPtr; }	
			vecNoblePtrs.clear();
			vecWarriorPtrs.clear();
		}
	}
	warriorFile.close();
}