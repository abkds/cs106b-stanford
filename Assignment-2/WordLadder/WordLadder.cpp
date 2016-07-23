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
#include <set>
#include <fstream>
#include "lexicon.h"

const std::string alphabets = "abcdefghijklmnopqrstuvwxyz";

/* Function prototypes */
std::vector<std::string> findLadder(std::string source, std::string destination,
	Lexicon& lexicon);

template <typename T>
void printVector(std::vector<T>& vec, std::string separator);

std::set<std::string> oneDistanceWords(std::string word, Lexicon& lexicon);

/* Main Program */
int main() {
	/* Load the lexicon */
	Lexicon english("EnglishWords.txt");

	while (true) {
		std::string source, destination;
		std::cout << "Enter start word (RETURN to quit): ";

		getline(std::cin, source);

		if (source.size() == 0) {	 // RETURN has been entered
			std::cout << "GoodBye !" << std::endl;
			break;
		}

		std::cout << "Enter the ending word: ";
		getline(std::cin, destination);

		std::cout << "Searching..." << std::endl;

		std::vector<std::string> ladder;
		if (english.contains(source) && english.contains(destination)) {
			ladder = findLadder(source, destination,
				english);
		}

		if (ladder.size() > 0) {
			std::cout << "Ladder found: ";
			printVector(ladder, " -> ");
			std::cout << std::endl;
		} else {
			std::cout << "No word ladder could be find." << std::endl;
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
	return 0;
}

/*
 * Funcion: findLadder
 * Usage: ladder = findLadder("work", "play", english);
 * ----------------------------------------------------
 * Finds a shortest ladder between two words according to a given lexicon.
 * A ladder is constructed of words, in which at most one letter is changed
 * and the word is present in the given lexicon.
 *
 * Example:
 * 		source: work, destination: play, lexicon: english
 * 		ladder: work -> form -> foam -> flam -> flay -> play
 *
 * The function uses breadth-first search strategy to find the most optimal
 * ladder. If the ladder doesn't exist it returns an empty vector.
 */
std::vector<std::string> findLadder(std::string source, std::string destination,
	Lexicon& lexicon) {
	std::vector<std::string> ladder;

	/* Queue to hold the ladder processed using bfs */
	std::queue<std::vector<std::string> > bfsQueue;

	/* First ladder contains the source word itself */
	ladder.push_back(source);

	/* Set to maintain the set of words already set in queue */
	std::set<std::string> wordsSeen;

	/*
	 * Iterate over all the one word distance words in the lexicon,
	 * and enqueue them. While dequeuing check whether the last element
	 * of ladder is the destination. If there are no more ladders to
	 * process, then there is no way to reach from source to destination
	 * using this lexicon.
	 *
	 * Note: While pushing a new word into the ladder, it is checked
	 * whether the word has been already processed, if it is, it's
	 * neglected. If the word was already processed (in a previous ladder),
	 * which would have been of smaller length, then processing it again
	 * would result in a sub-optimal queue.
	 */
	bfsQueue.push(ladder);             /* Push the initial ladder */
	vector<std::string> currentLadder; /* Current ladder to process */
	wordsSeen.insert(source);

	while (!bfsQueue.empty()) {
		/* dequeue the current ladder */
		currentLadder = bfsQueue.front();
		bfsQueue.pop();

		if (currentLadder.back() == destination) {
			return currentLadder;
		}

		/* add end word of current queue to set of words processed */
		std::set<std::string> wordsOneDistanceAway;
		wordsOneDistanceAway = oneDistanceWords(currentLadder.back(),
			lexicon);

		/* Iterate over all words one character away in lexicon */
		for (auto it = wordsOneDistanceAway.begin();
			it != wordsOneDistanceAway.end();
			++it) {

			/* Make new ladder and push them to queue */
			if (wordsSeen.count(*it) == 0) {
				std::vector<std::string> nextLadder(currentLadder);
				nextLadder.push_back(*it);
				wordsSeen.insert(*it);
				bfsQueue.push(nextLadder);
			}
		}
	}

	ladder.clear();
	return ladder;
}

/*
 * Function: oneDistanceWords
 * Usage: words = oneDistanceWords("make", english);
 * -------------------------------------------------
 * Returns a set of words that are one distance away from
 * the current word in the lexicon
 */
std::set<std::string> oneDistanceWords(std::string word, Lexicon& lexicon) {
	std::set<std::string> words;

	std::string wordCopy = word;
	for (size_t i = 0; i < word.size(); i++) {
		for (size_t j = 0; j < alphabets.size(); j++) {
			word[i] = alphabets[j];
			if (word != wordCopy && lexicon.contains(word)) {
				words.insert(word);
			}
		}
		word = wordCopy;
	}

	return words;
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
