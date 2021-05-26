// The Protector Header defines the parent class Protector and the following
// derived classes: Wizard, Archer, Swordsman.

#include <iostream>
#include <string>

#ifndef PROTECTOR_H
#define PROTECTOR_H

namespace WarriorCraft {

	class Lord;

	class Protector {
	public:
		Protector(const std::string& aName, const int aStrength);
		virtual void yell() const = 0;
		void quit();

		// Getters
		std::string getName() const;
		int getStrength() const;
		Lord* getEmployerPtr() const;

		// Setters
		void setEmployer(Lord& aLord);
		void setEmployer();
		void setStrength(const int aStrength);
	private:
		std::string name;
		int strength;
		Lord* employer;
	};


	class Wizard : public Protector {
	public:
		Wizard(const std::string& aName, const int aStrength);
		void yell() const;
	};


	class Archer : public Protector {
	public:
		Archer(const std::string& aName, const int aStrength);
		void yell() const;
	};


	class Swordsman : public Protector {
	public:
		Swordsman(const std::string& aName, const int aStrength);
		void yell() const;
	};

}
#endif