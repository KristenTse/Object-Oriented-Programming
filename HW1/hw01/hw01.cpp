// Kristen Tse
// Homework 01
// The following program reads an encrypted file and decrypts it using letter rotation.

#include <iostream>
#include <string>
#include <fstream>
using namespace std;


// This function decrypts a given lowercase character using a given number of 
// rotations, wrapping around the lowercase alphabet if necessary. It takes 
// two parameters: encryptedChar, which is the character to be decrypted, and
// numRotations, which is the number of steps encryptedChar will be rotated.
// It returns the final decrypted character.
char decryptChar(char encryptedChar, const int numRotations) { 
	if (encryptedChar < 97 || encryptedChar > 122) { 
		return encryptedChar;
	}
	else {
		char newChar = (((encryptedChar - numRotations) - 122) % 26) + 122; 
		return newChar;
	}
}  


// This function decrypts each character in a given string, using the previous 
// function decryptChar(). It takes two parameters: text, which is the line of 
// text to be directly modified, and numRotations, which is the number of steps
// each encrypted character will be rotated. There is no return value.
void decryptString(string& text, const int numRotations) {
	// the following loop iterates through the length of the string and replaces 
	// each encrypted character with its decrypted counterpart.
	for (unsigned int pos = 0; pos < text.length(); pos++) {
		text[pos] = decryptChar(text[pos], numRotations);
	}
}


// The main function reads the file "encrypted.txt" line by line, decrypting
// each line character by character. It returns the final fully decrypted text.
int main() {
	ifstream encryptedFile("encrypted.txt");
	if (!encryptedFile) {
		cerr << "The file could not be opened.\n";
		exit(1);
	}
	// set first line in the file to the number of rotations:
	int givenNumRotations;
	encryptedFile >> givenNumRotations;
	string line;
	(getline(encryptedFile, line)); //get rid of extra newline character

	// decrypt each file line by line and put each line into finalDecryptedText;
	// new decrypted lines are added before existing lines in finalDecryptedText 
	// because encrypted file has reversed lines: 
	string finalDecryptedText;
	while (getline(encryptedFile, line)) {
		decryptString(line, givenNumRotations);
		finalDecryptedText = line + "\n" + finalDecryptedText;
	}
	cout << finalDecryptedText;
	encryptedFile.close();
}