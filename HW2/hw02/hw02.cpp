// Kristen Tse
// Homework 02
// The following program reads a file of commands from "warriors.txt" and calls
// the appropriate functions. The Warrior command creates new warrior objects,
// The Battle command displays the fighting warriors and the outcome, the 
// Status command displays all the warrior names and strengths.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Warrior {
	string name;
	int strength;
};

// function prototypes: 
void createWarrior(vector<Warrior>& vecWarriors, const string& name, 
	const int& strength);
void displayStatus(const vector<Warrior>& vecWarriors);
void battle(Warrior& warrior1, Warrior& warrior2);
int findWarriorIndex(const vector<Warrior>& vecWarriors, const string& name);

// The main function reads the file and checks if can be opened. It also pushes
// each word into a vector of words for easy indexing. It then iterates though 
// the vector and calls the appropriate function if a command word is seen.
int main() {
	ifstream warriorsFile("warriors.txt");
	if (!warriorsFile) {
		cout << "The file could not be opened." << endl;
		exit(1);
	}
	vector<Warrior> vecWarriors;
	string word;
	vector<string> vecWords;
	// push each word in the file into vecWords
	while (warriorsFile >> word) {
		vecWords.push_back(word);
	}
	size_t i = 0;
	while (i < vecWords.size()) {
		// if the Warrior command is seen, call createWarrior() using the name  
		// and strength given in the two succeeding indexes of vecWords.
		if (vecWords[i] == "Warrior") {
			createWarrior(vecWarriors, vecWords[i + 1], stoi(vecWords[i + 2]));
			i += 3;
		}
		// if the Battle command is seen, find the location of the two warriors 
		// in vecWarriors and call battle().
		else if (vecWords[i] == "Battle") {
			int firstWarriorIdx = findWarriorIndex(vecWarriors,
				vecWords[i + 1]);
			int secondWarriorIdx = findWarriorIndex(vecWarriors,
				vecWords[i + 2]);
			if (firstWarriorIdx == -1 || secondWarriorIdx == -1) {
				cerr << "Warrior not found!" << endl;
				break;
			}
			battle(vecWarriors[firstWarriorIdx], vecWarriors[secondWarriorIdx]);
			i += 3;
		}
		// the only other command is Status, so displayStatus() if no other 
		// command is found.
		else {
			displayStatus(vecWarriors);
			i += 1;
		}
	}
	warriorsFile.close();
}

// creates a warrior object from the given name and strength, and adds it to the
// end of the warrior vector. There is no return value.
void createWarrior(vector<Warrior>& vecWarriors, const string& name, 
	const int& strength) {
	Warrior newWarrior;
	newWarrior.name = name;
	newWarrior.strength = strength;
	vecWarriors.push_back(newWarrior);
}

// displays the number of warriors there are. Also displays names and strengths
// of each individual warrior. There is no return value.
void displayStatus(const vector<Warrior>& vecWarriors) {
	cout << "There are: " << vecWarriors.size() << " warriors" << endl;
	for (Warrior warrior : vecWarriors) {
		cout << "Warrior: " << warrior.name 
			 << ", strength: " << warrior.strength << endl;
	}
}

// displays which warriors are battling and the appropriate response based on 
// the outcome. Also adjusts the warrior's strengths after battle. There is no
// return value.
void battle(Warrior& warrior1, Warrior& warrior2) {
	// determine which warrior is stronger/weaker out of the two given
	Warrior& stronger = warrior1;
	Warrior& weaker = warrior2;
	if (warrior1.strength < warrior2.strength) {
		stronger = warrior2;
		weaker = warrior1;
	}
	cout << warrior1.name << " battles " << warrior2.name << endl;
	if (warrior1.strength == 0 && warrior2.strength == 0) {
		cout << "Oh, NO! They're both dead! Yuck!" << endl;
	}
	else if (warrior1.strength == warrior2.strength) {
		cout << "Mutual Annihilation: " << warrior1.name << " and " 
			 << warrior2.name << " die at each other's hands" << endl;
		warrior1.strength = 0;
		warrior2.strength = 0;
	}
	else if (weaker.strength == 0) {
		cout << "He's dead, " << stronger.name << endl;
	}
	else {
		cout << stronger.name << " defeats " << weaker.name << endl;
		stronger.strength -= weaker.strength;
		weaker.strength = 0;
	}
}

// finds the index in the warrior vector that matches the given name. Returns 
// the index if a match is found. Returns -1 if there is no matching name.
int findWarriorIndex(const vector<Warrior>& vecWarriors, const string& name) {
	for (size_t i = 0; i < vecWarriors.size(); ++i) {
		if (vecWarriors[i].name == name) {
			return i;
		}
	}
	return -1;
}