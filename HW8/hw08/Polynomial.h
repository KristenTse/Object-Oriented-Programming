// The Polynomial Header defines the class Polynomial 

#include <iostream>
#include <vector>

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H


struct Node {
	Node(int coefficient = 0, Node * next = nullptr)
		: coefficient(coefficient), next(next) {}
	int coefficient;
	Node* next;
};


class Polynomial {
	friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);

public:
	Polynomial();

	Polynomial(const std::vector<int>& vecPoly);

	Polynomial(const Polynomial& rhs);

	~Polynomial();

	Polynomial& operator=(const Polynomial& rhs);

	// This function help finds the second to last node in the polynomial.
	// This is only used in the operator+= function overload.
	Node* findSecondToLast() const;

	Polynomial& operator+=(const Polynomial& rhs);

	bool operator==(const Polynomial& rhs) const;

	bool operator!=(const Polynomial& rhs) const;

	int evaluate(const int n);

private:
	Node* header;
	int degree;
};

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);

void doNothing(Polynomial temp);

#endif