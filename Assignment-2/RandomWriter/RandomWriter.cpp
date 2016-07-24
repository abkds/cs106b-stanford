/*
 * File: RandomWriter.cpp
 * ----------------------
 *
 * This file implements a random writer which generates text
 * by reading a source text and using a Markov model of order
 * k. 'k' is provided by the user as input.
 */
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include "random.h"

/* Function prototypes */
void OpenUserFile(std::ifstream& infile);

void generateOccurenceMap(std::ifstream& input,
	std::map<std::string, std::vector<char> >& occurenceMap, int order);

int getInteger(std::string prompt);

template <typename T>
void printVector(std::vector<T>& vec, std::string separator);

void generateRandomText(std::map<std::string, std::vector<char> >& occurenceMap,
	int numCharacters);

std::string findSeed(std::map<std::string, std::vector<char> >& occurenceMap);

/* Main Program */
int main() {

	std::ifstream input;
	OpenUserFile(input);

	int order;
	while (true) {
		order = getInteger("Enter the Markov order[1-10]: ");
		if (order >= 1 && order <= 10) break;
	};

	std::map<std::string, std::vector<char> > occurenceMap;
	generateOccurenceMap(input, occurenceMap, order);
	generateRandomText(occurenceMap, 2000);

	return 0;
}

/*
 * Function: OpenUserFile
 * Usage: OpenUserFile(infile);
 * ----------------------------
 * Opens a user file by prompting the name of file to the user. If the user
 * enters a wrong file name, then the program reprompts the user to enter
 * the correct file name, until the file is open. Takes ifstream object as
 * argument by reference, which is set to the file being opened.
 */
void OpenUserFile(std::ifstream& infile) {
	std::string filename;
	while (true) {
		std::cout << "Enter the filename: ";
		getline(std::cin, filename);
		infile.open(filename.c_str());
		if (infile.is_open()) return;
		std::cout << "Invalid file name. Try again." << std::endl;
		infile.clear();
	}
}

/*
 * Function: generateOccurenceMap
 * Usage: generateOccurenceMap(input, occurenceMap, 3);
 * -------------------------------------------------------
 * Generates a occurence map, from a stream of input characters
 * for a particular order 'k'. 'k' characters are taken as the
 * initial text. A vector is constructed of all the possible single
 * characters that occur after the text. Then next character is taken
 * into the taken and the first character is left out, similarly the
 * entire occurence map is generated. Order is in range [1-10]
 */
void generateOccurenceMap(std::ifstream& input,
	std::map<std::string, std::vector<char> >& occurenceMap, int order) {
	std::string text;

	char ch;
	for (int i = 0; i < order; i++) {
		input.get(ch);
		text += ch;
	}

	while (input.get(ch)) {
		occurenceMap[text].push_back(ch);
		text = text.substr(1) + ch;
	}
}

/*
 * Function: getInteger
 * Usage: getInteger("Enter integer: ");
 * -------------------------------------
 * Returns an integer after reading from the standard console,
 * Checks whether integer is entered correctly or not.
 */
int getInteger(std::string prompt) {
	int result;

	while (true) {
		std::cout << prompt;
		std::stringstream converter;
		std::string line;
		getline(std::cin, line);
		converter << line;
		converter >> result;

		if (converter.fail()) {
			std::cout << "Illegal integer format. Try again." << std::endl;
		} else {
			char remaining;
			if (converter.get(remaining)) {
				std::cout << "Illegal integer format. Try again." << std::endl;
			} else {
				return result;
			}
		}
	}
}


/*
 * Function: findSeed
 * Usage: findSeed(occurenceMap);
 * ------------------------------
 * Returns a seed for an instance of particular map. String with highest
 * number of occurences is the intial seed.
 */
std::string findSeed(std::map<std::string, std::vector<char> >& occurenceMap) {

	/* Occurences can never be negative, -1 is a sentinel value */
	size_t maxOccurence = 0;
	std::vector<std::string> seedVector;

	std::string seed = "";

	for (auto it = occurenceMap.begin(); it != occurenceMap.end(); ++it) {
		if ((it->second).size() > maxOccurence) {
			maxOccurence = (it->second).size();
			seed = (it->first);
		}
	}

	for (auto it = occurenceMap.begin(); it != occurenceMap.end(); ++it) {
		if ((it->second).size() == maxOccurence) {
			seedVector.push_back(it->first);
		}
	}

	return seedVector[randomInteger(0, seedVector.size()-1)];
}

/*
 * Function: generateRandomText
 * Usage: generateRandomText(occurenceMap, 2000);
 * ----------------------------------------------
 * Outputs random text based on the Markov model represented by the occurenceMap,
 * the most common phrase is taken as the initial seed and the text is then
 * sequentially constructed for 'numCharacters'.
 * If a particular phrase doesn't have any occurences associated, then
 * text generatation is terminated.
 */
void generateRandomText(std::map<std::string, std::vector<char> >& occurenceMap,
	int numCharacters) {

	std::string seed = findSeed(occurenceMap);

	for (int i = 0; i < numCharacters; i++) {
		if (occurenceMap[seed].size() == 0) break;
		char ch = occurenceMap[seed][randomInteger(0, occurenceMap[seed].size()-1)];
		std::cout.put(ch);
		seed = seed.substr(1) + ch;
	}

	std::cout << std::endl;

}

/*
 * Funcion: printVector
 * Usage: printVector(vec, ", ");
 * ------------------------------
 * Prints a vector of objects seprated by the separator.
 *
 * 		eg v = {1, 2, 3}
 *      printVector(v, " -> ");
 *      1 -> 2 -> 3
 * Doesn't print an endline after printing the vector.
 */
template <typename T>
void printVector(std::vector<T>& vec, std::string separator) {
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		if (it != vec.begin()) std::cout << separator;
		std::cout << *it;
	}
}
