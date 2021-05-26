// The implementation for Protector and its derived classes.

#include <iostream>
#include <string>
#include "Protector.h"
#include "Noble.h"
using namespace std;
using namespace WarriorCraft;


// Protector Implementation
Protector::Protector(const string& aName, const int aStrength)
	: name(aName), strength(aStrength), employer(nullptr) {}
void Protector::quit() {
	employer->removeFromArmy(*this);
	employer = nullptr;
}
// Getters
string Protector::getName() const { return name; }
int Protector::getStrength() const { return strength; }
Lord* Protector::getEmployerPtr() const { return employer; }
// Setters
void Protector::setEmployer(Lord& aLord) { employer = &aLord; }
void Protector::setEmployer() { employer = nullptr; }
void Protector::setStrength(const int aStrength) { strength = aStrength; }


// Wizard Implmentation
Wizard::Wizard(const string& aName, const int aStrength) 
	: Protector(aName, aStrength) {}
void Wizard::yell() const { cout << "POOF!\n"; }


// Archer Implmentation
Archer::Archer(const string& aName, const int aStrength) 
	: Protector(aName, aStrength) {}
void Archer::yell() const {
	cout << "TWANG! " << Protector::getName() <<
		" says: Take that in the name of my lord, " 
		<< Protector::getEmployerPtr()->getName() << endl;
}


// Swordsman Implmentation
Swordsman::Swordsman(const string& aName, const int aStrength) 
	: Protector(aName, aStrength) {}
void Swordsman::yell() const {
	cout << "CLANG! " << Protector::getName() <<
		" says: Take that in the name of my lord, " 
		<< Protector::getEmployerPtr()->getName() << endl;
}
