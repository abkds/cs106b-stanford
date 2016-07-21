/*
 * File: NumericConversion.cpp
 * ---------------------------
 *
 * This program implements function to convert
 * integer to string and vice versa.
 */

#include <iostream>
#include <string>
#include <sstream>

/* Function prototypes */

std::string intToString(int n);
int stringToInt(std::string str);

/* Main program */

int main() {
    int n = -1729;
    /* Outputs string concatenation result -17291 */
    std::cout << intToString(n) + "1" << std::endl;

    /* Outputs the integer sum between -1729 and 1 */
    std::cout << stringToInt("-1729") + 1 << std::endl;

    return 0;
}


/*
 * Function: intToString
 * Usage: str = intToString(9)
 * ---------------------------
 * Converts a integer to string by using stringstreams
 * stringstreams takes in an integer and redirects the
 * output as string.
 */
std::string intToString(int n) {
    std::stringstream converter;
    converter << n;
    std::string result;
    converter >> result;
    return result;
}

/*
 * Function: stringToInt
 * Usage: value = stringToInt("-200")
 * ----------------------------------
 * Converts a string to an integer and returns it
 * assumes that the string is a valid integer.
 */
int stringToInt(std::string str) {
    std::stringstream converter;
    converter << str;
    int n;
    converter >> n;
    return n;
}
