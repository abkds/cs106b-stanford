/*
 * File: RandomSubsets.cpp
 * ----------------------
 * This file is the starter project for the Random Subsets problem
 * on Assignment #3.
 */
#include <algorithm>
#include <iostream>
#include <fstream>
#include <set>
#include <iterator>
#include "random.h"

/* Given a set of integers, returns a uniformly-random subset of that
 * set.
 */
std::set<int> randomSubsetOf(std::set<int>& s);

void OpenUserFile(std::ifstream& infile);

void printSet(std::set<int>& s);


int main() {
	std::set<int> s;
	std::ifstream input;
	OpenUserFile(input);

	copy(std::istream_iterator<int>(input), std::istream_iterator<int>(),
		inserter(s, s.begin()));

	std::set<int> randomSubset = randomSubsetOf(s);
	printSet(randomSubset);

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
 * Function: randomSubsetOf
 * Usage: randomSubset = randomSubsetOf(primesLessThan100);
 * --------------------------------------------------------
 * Returns a random subset from a set. Each element in the set
 * is choosen on the basis of a coin flip, and is included in
 * the random subset.
 *
 * Implemented using the recursive strategy, first element is
 * choosen, if the flip says yes it is put in the final subset
 * otherwise not. The remaining set is then taken into
 * consideration.
 */
std::set<int> randomSubsetOf(std::set<int>& s) {
	std::set<int> randomSubset;

	/*
	 * Base case, empty set is the only random subset of
	 * empty set.
	 */
	if (s.size() == 0) return randomSubset;

	/* Choose the first element */
	auto beginIterator = s.begin();
	int element = *beginIterator;
	s.erase(beginIterator);

	/* Unbiased coin flip: choose the first element or not */
	if (randomChance(0.5)) {
		randomSubset.insert(element);
	}

	/* Find a random subset from remaining */
	std::set<int> randomSubsetOfRemaining = randomSubsetOf(s);
	randomSubset.insert(randomSubsetOfRemaining.begin(), randomSubsetOfRemaining.end());

	return randomSubset;
}

/*
 * Function: printSet
 * Usage: printSet(set);
 * ---------------------
 * Prints the content of a set of integers.
 */
void printSet(std::set<int>& s) {
	copy(s.begin(), s.end(), std::ostream_iterator<int>(std::cout, ", "));
	std::cout << std::endl;
}
