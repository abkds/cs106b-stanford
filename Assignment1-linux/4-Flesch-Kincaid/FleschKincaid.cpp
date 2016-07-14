/*******************************************************************
 * File: FleschKincaid.cpp
 *
 * A program that approximates the Flesch-Kincaid grade level of a
 * piece of text.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "tokenscanner.h"

/* Flesch-Kincaid formula constants */
const double C_0 = -15.59;
const double C_1 = 0.39;
const double C_2 = 11.8;

/* Sentence ending characters */
const std::string sentenceEnd = ".?!";

/*
 * Function: OpenUserFile
 * Usage: OpenUserFile(infile);
 * ----------------------------
 * Opens a user file by prompting the name of file to the user. If the user
 * enters a wrong file name, then the program reprompts the user to enter
 * the correct file name, until the file is open. Takes ifstream object as
 * argument by reference, which is set to the file being opened.
 */
void OpenUserFile(std::ifstream& infile);

/*
 * Function: ReadTokens
 * Usage: ReadTokens(scanner);
 * -----------------------------------------
 * Reads the tokens from a scanner, display them to the output stream.
 */
void PrintTokens(TokenScanner scanner);

/*
 * Function: FleschKincaidGrade
 * Usage: double grade = FleschKincaidGrade(syllables, words, sentences)
 * ---------------------------------------------------------------------
 * Returns the Flesch Kincaid Grade, with the given number of syllables,
 * words and sentences, as calculated by the empirical formula.
 *
 * 			C_0 + C_1 * (words / sentences) + C_2 * (syllables / words)
 */
double FleschKincaidGrade(int syllables, int words, int sentences);

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
	int& words, int& sentences);

/*
 * Function: CountSyllables
 * Usage: int syllables = CountSyllables("program");
 * -------------------------------------------------
 * Counts the number of syllables of a word.
 * TODO [documentation]
 */
int CountSyllables(std::string word);

int main() {
	std::ifstream infile;
	OpenUserFile(infile);

	TokenScanner scanner(infile);

	scanner.ignoreWhitespace();
	// Count the following characters as part of word
	scanner.addWordCharacters("'");

	PrintTokens(scanner);
	// int syllables, word, sentences;
	// CountTextInformation(scanner, syllables, word, sentences);
	// PrintTextInformation(syllables, word, sentences);

	return 0;
}

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

void PrintTokens(TokenScanner scanner) {
	while (scanner.hasMoreTokens()) {
		std::string token = scanner.nextToken();
		std::cout << "Token: [" << token << "]" << " Type: ("
			<< scanner.getTokenType(token) << ")" << std::endl;
	}
}

double FleschKincaidGrade(int syllables, int words, int sentences) {
	double grade = C_0 + C_1 * (words * 1.0 / sentences) +
			C_2 * (syllables * 1.0 / words);
	return grade;
}

void CountTextInformation(TokenScanner scanner, int& syllables,
	int& words, int& sentences) {

	words = 0;
	syllables = 0;
	sentences = 0;

	while (scanner.hasMoreTokens()) {
		std::string token = scanner.nextToken();
		std::cout << "Token: [" << token << "]  ";

		int syllablesInWord;
		TokenType tokenType = scanner.getTokenType(token);
		if (tokenType == WORD) {
			syllablesInWord = CountSyllables(token);

			std::cout << "(word; " << syllablesInWord <<
				<< (syllablesInWord > 1) ? " syllables" : "syllable";
			words++;
		} else if (tokenType == OPERATOR) {

		}

		std::cout << std::endl;
	}

}
