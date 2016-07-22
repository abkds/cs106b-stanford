/*
 * File: WordLadder.cpp
 * --------------------
 *
 * This file implements a program to find the shortest ladder between
 * two English words. EnglishWords.txt contains a lexicon of all the
 * English words.
 *
 * A sample run of the program for source word [work] and destination
 * word [play] would result in the shortest ladder as depicted:
 *
 *		 work fork form foam flam flay play
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include "lexicon.h"

/* Function prototypes */
std::vector<std::string> findLadder(std::string source, std::string destination,
	Lexicon lexicon);

template <typename T>
void printVector(std::vector<T> vec, std::string separator);

/* Main Program */
int main() {

	/* Load the lexicon */
	Lexicon english("EnglishWords.txt");

	std::string word = "xx";

	/*for (char c0 = 'a'; c0 <= 'z'; c0++) {

		word[0] = c0;
		for (char c1 = 'a'; c1 <= 'z'; c1++) {

			word[1] = c1;
			if (english.contains(word)) {
				std::cout << word << std::endl;
			}
		}
	}*/

	while (true) {
		std::string source, destination;
		std::cout << "Enter start word (RETURN to quit): ";

		getline(std::cin, source);

		if (source.size() == 0) {	 /* RETURN has been entered */
			std::cout << "GoodBye !" << std::endl;
			break;
		}

		std::cout << "Enter the ending word: ";
		getline(std::cin, destination);

		std::cout << "Searching..." << std::endl;

		if (english.contains(source) && english.contains(destination)) {
			std::vector<std::string> ladder = findLadder(source, destination,
				english);

			std::cout << "Ladder found: ";
			printVector(ladder, " -> ");
			std::cout << std::endl;
		} else {
			std::cout << "No word ladder could be find." << std::endl;
		}

		std::cout << std::endl;
	}

	return 0;
}

std::vector<std::string> findLadder(std::string source, std::string destination,
	Lexicon lexicon) {
	std::vector<std::string> ladder;
	return ladder;
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
void printVector(std::vector<T> vec, std::string separator) {
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		if (it != vec.begin()) std::cout << separator;
		std::cout << *it;
	}
}
