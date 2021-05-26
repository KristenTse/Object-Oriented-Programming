// The Noble Header defines the parent class Noble and the following
// derived classes: Lord, PersonWithStrengthToFight.

#include <iostream>
#include <string>
#include <vector>

#ifndef NOBLE_H
#define NOBLE_H

namespace WarriorCraft {

	class Protector;

	class Noble {
	public:
		Noble(const std::string& aName);

		void battle(Noble& otherNoble);
		virtual double determineStrength() const = 0;
		virtual void setStrength(const int ratio) = 0;
		virtual void yell() const = 0;

		// Getters
		std::string getName() const;
		bool getIsDead() const;

	private:
		std::string name;
		bool dead;
	};


	class Lord : public Noble {
	public:
		Lord(const std::string& aName);
		bool hires(Protector& aProtector);
		bool fires(Protector& aProtector);
		void removeFromArmy(Protector& aProtector);
		double determineStrength() const;
		void setStrength(const int ratio);
		void yell() const;
	private:
		std::vector<Protector*> vecArmy;
	};


	class PersonWithStrengthToFight : public Noble {
	public:
		PersonWithStrengthToFight(const std::string& aName, 
			const int aStrength);
		double determineStrength() const;
		void setStrength(const int ratio);
		void yell() const;
	private:
		int strength;
	};

}
#endif