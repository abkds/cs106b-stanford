/*******************************************************************
 * File: FleschKincaid.cpp
 *
 * A program that approximates the Flesch-Kincaid grade level of a
 * piece of text.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include "tokenscanner.h"
#include "strlib.h"

/* Flesch-Kincaid formula constants */
const double C_0 = -15.59;
const double C_1 = 0.39;
const double C_2 = 11.8;

/* Sentence ending characters */
const std::string sentenceEnd = ".?!";

/* Syllable characters */
const std::string syllableCharacters = "aeiouy";

/* Function prototypes */
void OpenUserFile(std::ifstream& infile);

void PrintTokens(TokenScanner scanner);

double FleschKincaidGrade(int syllables, int words, int sentences);

void CountTextInformation(TokenScanner scanner, int& syllables,
	int& words, int& sentences);

int CountSyllables(std::string word);

void PrintTextInformation(int syllables, int words, int sentences);

int main() {

	std::ifstream infile;
	OpenUserFile(infile);

	TokenScanner scanner(infile);

	/* Ignore white spaces as tokens */
	scanner.ignoreWhitespace();

	/* Count apostroophe as part of word */
	scanner.addWordCharacters("'");

	int syllables, words, sentences;
	CountTextInformation(scanner, syllables, words, sentences);
	PrintTextInformation(syllables, words, sentences);

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
 * Function: PrintTokens
 * Usage: PrintTokens(scanner);
 * -----------------------------------------
 * Reads the tokens from a scanner, display them to the output stream.
 */
void PrintTokens(TokenScanner scanner) {
	while (scanner.hasMoreTokens()) {
		std::string token = scanner.nextToken();
		std::cout << "Token: [" << token << "]" << " Type: ("
			<< scanner.getTokenType(token) << ")" << std::endl;
	}
}

/*
 * Function: FleschKincaidGrade
 * Usage: double grade = FleschKincaidGrade(syllables, words, sentences)
 * ---------------------------------------------------------------------
 * Returns the Flesch Kincaid Grade, with the given number of syllables,
 * words and sentences, as calculated by the empirical formula.
 *
 * 			C_0 + C_1 * (words / sentences) + C_2 * (syllables / words)
 */
double FleschKincaidGrade(int syllables, int words, int sentences) {
	double grade = C_0 + C_1 * (words * 1.0 / sentences) +
			C_2 * (syllables * 1.0 / words);
	return grade;
}

/*
 * Function: CountTextInformation
 * Usage: CountTextInformation(scanner, syllables, words, sentences)
 * --------------------------------------------------------
 * Counts the number of syllables, words and sentences in a
 * given text, by the help of scanning object. The words and
 * sentences are counted using a loop and on each word a Function
 * is called to count the syllables.
 */
void CountTextInformation(TokenScanner scanner, int& syllables,
	int& words, int& sentences) {

	words = 0;
	syllables = 0;
	sentences = 0;

	while (scanner.hasMoreTokens()) {
		std::string token = scanner.nextToken();
//		std::cout << "Token: [" << token << "]  ";

		int syllablesInWord;
		TokenType tokenType = scanner.getTokenType(token);
		if (tokenType == WORD && isalpha(token[0])) {
			syllablesInWord = CountSyllables(token);

//			std::cout << "(word; " << syllablesInWord
//				<< (syllablesInWord > 1 ? " syllables" : " syllable") << ")";
			words++;
			syllables += syllablesInWord;
		} else if (tokenType == OPERATOR) {
			/* Check if the particular token depicts end of sentence */
			if (sentenceEnd.find(token) != std::string::npos) {
//				std::cout << "(end of sentence)";
				sentences++;
			}
		}

//		std::cout << std::endl;
	}

}

/*
 * Function: CountSyllables
 * Usage: int syllables = CountSyllables("program");
 * -------------------------------------------------
 * Returns the number of syllables of a word.
 *
 * All vowels (including 'y') are considered as syllables.
 * Vowels that have vowels directly before them are counted as single syllable.
 * 'e' at the end of string is not considered as syllable.
 *
 * If the count comes to be zero as in case of word 'me', applying the above
 * rules, the syllable count should be taken as 1 instead of 0.
 */
int CountSyllables(std::string token) {
	std::vector<std::string> syllables;

	token = toLowerCase(token);

	/* Sentinel value for keeping start of vowel group */
	int start = -1;
	for (int i = 0; i < token.size(); i++) {
		if (syllableCharacters.find(token[i]) != std::string::npos) {
			if (start == -1) {
				start = i;
			}
		} else {
			if (start != -1) {
				syllables.push_back(token.substr(start, i-start));
				start = -1;
			}
		}
	}

	/* Syllable at the end of string */
	if (start != -1) {
		syllables.push_back(token.substr(start));
	}

	std::string reverseToken = token;
	reverse(reverseToken.begin(), reverseToken.end());

	if (!syllables.empty() && (syllables.back() == "e") && (reverseToken.find('e') == 0)) {
		syllables.pop_back();
	}

	/* If the syllable count is zero return 1 */
	return syllables.size() == 0 ? 1 : syllables.size();
}

/*
 * Function: PrintTextInformation
 * Usage: PrintTextInformation(syllables, word, sentences)
 * -------------------------------------------------------
 * Prints the number of syllables, word, sentences and Flesch-Kincaid
 * grade of a text.
 */
void PrintTextInformation(int syllables, int words, int sentences) {
	std::cout << "Words: " << words << std::endl;
	std::cout << "Sentences: " << sentences << std::endl;
	std::cout << "Syllables: " << syllables << std::endl;
	std::cout << "Grade level: " << FleschKincaidGrade(syllables, words, sentences)
		<< std::endl;
	return;
}
