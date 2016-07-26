/*
 * File: Subsequences.cpp
 * ----------------------
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 */

#include <iostream>
#include <string>

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(std::string text, std::string subsequence);

int main() {
    std::string text, subsequence;

    std::cout << "Enter the text: ";
    getline(std::cin, text);
    std::cout << "Enter the subsequence to search for: ";
    getline(std::cin, subsequence);

	std::cout << "Is \"" << subsequence << "\" a subsequence of \"" << text
    << "\" ? : " << std::boolalpha << isSubsequence(text, subsequence);
    std::cout << std::endl;
}

/*
 * Function: isSubsequence
 * Usage: if(isSubsequence("Positivity", "otvy") ...
 * -------------------------------------------------
 * Returns whether a string is a subsequence of a text or not.
 *
 * Implementation notes:
 * Recursive insight, peel off characters from the text string, until and
 * unless there is a character match between the text string's first character
 * and subsequence (to find) string's first character. If there a match, peel
 * off the character from subsequence string and recurse.
 *
 * Base case:
 *     Empty string is the subsequence of every text.
 *     No string is subsequence of empty string. (Except for empty string)
 *
 * If we run of text string with subsequence string remaining return false.
 */
bool isSubsequence(std::string text, std::string subsequence) {

    /* Base cases */
    if (subsequence.size() == 0) return true;
    if (text.size() == 0 && subsequence.size() != 0) return false;

    /* If first charachters match, recurse on remaining */
    if (text[0] == subsequence[0]) {
        return isSubsequence(text.substr(1), subsequence.substr(1));
    }
    /* If first charachters don't match
     * Peel a character from the text only.
     */
    else {
        return isSubsequence(text.substr(1), subsequence);
    }
}
