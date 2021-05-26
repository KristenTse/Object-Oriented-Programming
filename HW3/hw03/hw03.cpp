// Kristen Tse
// Homework 03
// The following program reads a file of warrior commands and calls the 
// appropriate functions. "Warrior" initializes a warrior object, "Battle" 
// battles two warriors and determines the winner. "Status" displays the 
// number of warriors, their weapons, and their remaining strength. This was 
// implemented using OOP techniques.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

// Create a Warrior class with a private class Weapon. The Warrior constuctor 
// intializes a Weapon object. The Warrior class also has a method for battling
// two warriors. Both classes have overloaded the operator method.
class Warrior {
	friend ostream& operator<<(ostream& os, const Warrior& theWarrior) {
		os << "Warrior: " << theWarrior.name << ", " << theWarrior.weapon;
		return os;
	}
public:
	Warrior(const string& nameWarrior, const string& weaponName, int weaponStrength) : 
		name(nameWarrior), weapon(weaponName, weaponStrength) {}
	
	string getWarriorName() const { return name; }

	void battle(Warrior& warrior) {
		cout << name << " battles " << warrior.name << endl;
		// If both warriors have a strength of 0:
		if (weapon.getStrength() == 0 && warrior.weapon.getStrength() == 0) {
			cout << "Oh, NO! They're both dead! Yuck!\n";
		}
		// If both warriors have the same strength:
		else if (weapon.getStrength() == warrior.weapon.getStrength()) {
			cout << "Mutual Annihilation: " << name << " and "
				<< warrior.name << " die at each other's hands\n";
			weapon.setStrength(0);
			warrior.weapon.setStrength(0);
		} 
		// If this warrior is already dead:
		else if (weapon.getStrength() == 0) {
			cout << "He's dead, " << warrior.name << endl;
		}
		// If the warrior used as a parameter is dead:
		else if (warrior.weapon.getStrength() == 0) {
			cout << "He's dead, " << name << endl;
		}
		// If this warrior is stronger than the warrior used as a parameter: 
		else if (weapon.getStrength() > warrior.weapon.getStrength()) {
			cout << name << " defeats " << warrior.name << endl;
			weapon.setStrength(weapon.getStrength() - 
				warrior.weapon.getStrength());
			warrior.weapon.setStrength(0);
		}
		// If the warrior used as a parameter is stronger than this warrior:
		else {
			cout << warrior.name << " defeats " << name << endl;
			weapon.setStrength(warrior.weapon.getStrength() - 
				weapon.getStrength());
			weapon.setStrength(0);
		}
	}
private:
	class Weapon {
		friend ostream& operator<<(ostream& os, const Weapon& theWeapon) {
			os << "weapon: " << theWeapon.name << ", " << theWeapon.strength;
			return os;
		}
	public:
		Weapon(const string& nameWeapon, int strengthWeapon) :
			name(nameWeapon), strength(strengthWeapon) {}

		string getName() const { return name; }
		int getStrength() const { return strength; }
		void setStrength(int amount) {
			if (amount < 0) {
				strength = 0;
			}
			else {
				strength = amount;
			}
		}
	private:
		string name;
		int strength;
	};
	string name;
	Weapon weapon;
};

// Iterate through the warrior vector and display each warrior's name, weapon,
// and strength.
void displayStatus(const vector<Warrior>& vecWarriors) {
	cout << "There are: " << vecWarriors.size() << " warriors\n";
	for (Warrior warrior : vecWarriors) {
		cout << warrior << endl;
	}
}

// Iterate through the warrior vector to find the warrior with the given name. 
// Returns the index if a match is found, otherwise returns -1.
int findWarriorIndex(const vector<Warrior>& vecWarriors, const string& name) {
	for (size_t i = 0; i < vecWarriors.size(); ++i) {
		if (vecWarriors[i].getWarriorName() == name) {
			return i;
		}
	}
	return -1;
}

// The main function opens and reads the file, then calls the appropriate 
// functions based off the commands in the file.
int main() {
	// Ask the user for the filename until the file can be opened.
	ifstream warriorFile;
	string fileName;
	while (!warriorFile.is_open()) {
		cout << "Enter the name of the file: ";
		cin >> fileName;
		warriorFile.open(fileName);
		if (!warriorFile) {
			cerr << "The file could not be opened.\n";
			warriorFile.clear();
		}
	}
	// Create a warrior vector to hold warriors.
	vector<Warrior> vecWarriors;

	// Read the file and call the appropriate functions.
	string command, nameOne, nameTwo, weaponName;
	int strength;
	while (warriorFile >> command) {
		if (command == "Warrior") {
			warriorFile >> nameOne >> weaponName >> strength;
			vecWarriors.push_back(Warrior(nameOne, weaponName, strength));
		}
		else if (command == "Battle") {
			warriorFile >> nameOne >> nameTwo;
			int indexOne = findWarriorIndex(vecWarriors, nameOne);
			int indexTwo = findWarriorIndex(vecWarriors, nameTwo);
			if (indexOne == -1 || indexTwo == -1) {
				cerr << "Warrior not found.\n";
				exit(1);
			}
			vecWarriors[indexOne].battle(vecWarriors[indexTwo]);
		}
		else if (command == "Status") {
			displayStatus(vecWarriors);
		}
	}
	warriorFile.close();
}