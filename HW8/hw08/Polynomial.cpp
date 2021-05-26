// The implementation for the class Polynomial

#include <iostream>
#include <vector>
#include <string>
#include "Polynomial.h"
using namespace std;


ostream& operator<<(ostream& os, const Polynomial& rhs) {
	string polynomial = "";
	Node* currNode = rhs.header->next;
	int degree = 0;
	while (currNode != nullptr) {
		string term = "";
		if ((currNode->coefficient != 0 && currNode->coefficient != 1) ||
			(currNode->coefficient == 0 && degree == 0) ||
			(currNode->coefficient == 1 && degree == 0)) {
			term = to_string(currNode->coefficient);
		}
		if (currNode->coefficient != 0 && degree != 0) {
			term += "x";
			if (degree != 1) {
				term += "^" + to_string(degree);
			}
		}
		if (polynomial != "" && term != "") {
			polynomial = term + " + " + polynomial;
		}
		else {
			polynomial = term + polynomial;
		}
		++degree;
		currNode = currNode->next;
	}
	os << polynomial;
	return os;
}


Polynomial::Polynomial() : degree(0), header(new Node()) {
	header->next = new Node(0);
}

Polynomial::Polynomial(const vector<int>& vecPoly)
	: degree(-1), header(new Node()) {
	int startIdx = vecPoly.size() - 1;
	// Check for empty 0's at the beginning of the vector and find the
	// first non-zero.
	for (size_t i = 0; i < vecPoly.size(); i++) {
		if (vecPoly[i] != 0) {
			startIdx = i;
			break;
		}
	}
	// Create the nodes beginning from the first non-zero in the vector.
	for (size_t i = startIdx; i < vecPoly.size(); i++) {
		header->next = new Node(vecPoly[i], header->next);
		++degree;
	}
}

Polynomial::Polynomial(const Polynomial& rhs)
	: degree(rhs.degree), header(new Node()) {
	Node* rightPtr = rhs.header->next;
	Node* leftPtr = header;
	// Copy each coefficient from rhs into this polynomial.
	while (rightPtr != nullptr) {
		leftPtr->next = new Node(rightPtr->coefficient);
		rightPtr = rightPtr->next;
		leftPtr = leftPtr->next;
	}
}

Polynomial::~Polynomial() {
	while (header != nullptr) {
		Node* nextNode = header->next;
		delete header;
		header = nextNode;
	}
}

Polynomial& Polynomial::operator=(const Polynomial& rhs) {
	if (this != &rhs) {
		degree = rhs.degree;
		// Delete the existing nodes in this polynomial.
		while (header != nullptr) {
			Node* nextNode = header->next;
			delete header;
			header = nextNode;
		}
		header = new Node(*rhs.header);
		Node* leftPtr = header;
		Node* rightPtr = rhs.header->next;
		// Copy over each coefficient from rhs into this polynomial.
		while (rightPtr != nullptr) {
			leftPtr->next = new Node(rightPtr->coefficient);
			rightPtr = rightPtr->next;
			leftPtr = leftPtr->next;
		}
	}
	return *this;
}

// This function help finds the second to last node in the polynomial.
// This is only used in the operator+= function overload.
Node* Polynomial::findSecondToLast() const {
	Node* currNode = header;
	while (currNode->next->next != nullptr) {
		currNode = currNode->next;
	}
	return currNode;
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
	Node* rightPtr = rhs.header;
	Node* leftPtr = header;
	// Traverse through the linked list until there are no more terms 
	// in rhs. Modify each corresponding term (with the same degree)
	// in this polynomial by adding the coefficients.
	while (rightPtr->next != nullptr) {
		if (leftPtr->next == nullptr) {
			leftPtr->next = new Node(rightPtr->next->coefficient);
			++degree;
		}
		else {
			leftPtr->next->coefficient += rightPtr->next->coefficient;
		}
		rightPtr = rightPtr->next;
		leftPtr = leftPtr->next;
	}
	// Modify the degree if there are 0's that need to be cleared.
	// If the terms with the hightest degree have a coefficient of 0, 
	// delete them from the list. I don't think the warning that says 
	// "Dereferencing NULL pointer..." is a problem because secondLast
	// should never be before the header. The header->next shouldn't be
	// NULL either due to the way I implemented the Polynomial 
	// constructors.
	Node* secondLast = findSecondToLast();
	while (secondLast->next->coefficient == 0) {
		delete secondLast->next;
		secondLast->next = nullptr;
		--degree;
		secondLast = findSecondToLast();
	}
	return *this;
}

bool Polynomial::operator==(const Polynomial& rhs) const {
	Node* rightPtr = rhs.header;
	Node* leftPtr = header;
	if (degree != rhs.degree) {
		return false;
	}
	// traverse through both lists and check each coefficient to see
	// if they match.
	while (rightPtr->next != nullptr && leftPtr->next != nullptr) {
		if (leftPtr->next->coefficient != rightPtr->next->coefficient) {
			return false;
		}
		rightPtr = rightPtr->next;
		leftPtr = leftPtr->next;
	}
	return true;
}

bool Polynomial::operator!=(const Polynomial& rhs) const {
	return !(*this == rhs);
}

int Polynomial::evaluate(const int n) {
	int sum = 0;
	unsigned degreeCount = 0;
	Node* currNode = header->next;
	// Evaluate each term at n, then add the term to the total sum.
	while (currNode != nullptr) {
		int term = 1;
		for (size_t i = 0; i < degreeCount; i++) {
			term *= n;
		}
		term *= currNode->coefficient;
		sum += term;
		++degreeCount;
		currNode = currNode->next;
	}
	return sum;
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
	Polynomial temp = lhs;
	return temp += rhs;
}

void doNothing(Polynomial temp) {}
