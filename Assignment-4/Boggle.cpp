/*
 * File: Boggle.cpp
 * ----------------
 * Implementation file for Boggle Game
 * Author: Abhishek K Das
 */

#include "Boggle.h"
#include "strlib/strlib.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <set>
#include <fstream>
#include <cstdlib>

/*
 * Constructor: Boggle
 * -------------------
 * Display welcome message, give instructions, load lexicon.
 * Initialize the boggle board, with user forced string or pre-defined
 * cubes.
 * For lexicon, using a set of strings to just get the membership of a
 * word.
 */
Boggle::Boggle() {
    loadLexicon();
    welcome();
    giveInstructions();
    askBoardSize();
    setBoardCharacters();
    drawBoard();
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */
void Boggle::welcome() const {
    std::cout << "Welcome!  You're about to play an intense game \n";
    std::cout << "of mind-numbing Boggle.  The good news is that \n";
    std::cout << "you might improve your vocabulary a bit.  The \n";
    std::cout << "bad news is that you're probably going to lose \n";
    std::cout << "miserably to this little dictionary-toting hunk \n";
    std::cout << "of silicon.  If only YOU had a gig of RAM..." << std::endl << std::endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the gloomy instructions for the user.
 */
void Boggle::giveInstructions() const {
    std::cout << std::endl;
    std::cout << "The boggle board is a grid onto which I \n";
    std::cout << "I will randomly distribute cubes. These \n";
    std::cout << "6-sided cubes have letters rather than \n";
    std::cout << "numbers on the faces, creating a grid of \n";
    std::cout << "letters on which you try to form words. \n";
    std::cout << "You go first, entering all the words you can \n";
    std::cout << "find that are formed by tracing adjoining \n";
    std::cout << "letters. Two letters adjoin if they are next \n";
    std::cout << "to each other horizontally, vertically, or \n";
    std::cout << "diagonally. A letter can only be used once \n";
    std::cout << "in each word. Words must be at least four \n";
    std::cout << "letters long and can be counted only once. \n";
    std::cout << "You score points based on word length: a \n";
    std::cout << "4-letter word is worth 1 point, 5-letters \n";
    std::cout << "earn 2 points, and so on. After your puny \n";
    std::cout << "brain is exhausted, I, the supercomputer, \n";
    std::cout << "will find all the remaining words and double \n";
    std::cout << "or triple your paltry score." << std::endl << std::endl;

    std::cout << "Press RETURN when you're ready...";
    std::string dummy;
    getline(std::cin, dummy);
}

/*
 * Private Function: loadLexicon
 * Usage: loadLexicon()
 * -----------------------------
 * Loads the lexicon from a source of text into
 * a set of string.
 */
void Boggle::loadLexicon() {
    std::ifstream input("EnglishWords.txt");

    if (!input.is_open()) {
        std::cerr << "Error: Couldn't open the file." << std::endl;
        exit(1);
    }

    std::copy(std::istream_iterator<std::string>(input), std::istream_iterator<std::string>(),
              std::inserter(lexicon, lexicon.begin()));
}

/*
 * Private Function: drawBoard
 * Usage: drwaBoard()
 * ---------------------------
 * Displays the boggle board to console.
 *
 * It looks like following:
 *      +---+---+---+---+---+
 *      | a | b | c | d | e |
 *      +---+---+---+---+---+
 *      | f | g | h | i | j |
 *      +---+---+---+---+---+
 *      | k | l | m | n | o |
 *      +---+---+---+---+---+
 *      | p | q | r | s | t |
 *      +---+---+---+---+---+
 *      | u | v | w | x | y |
 *      +---+---+---+---+---+
 */
void Boggle::drawBoard() const {

    for (int i = 0; i < board.size(); i++) {
        std::cout << "+---";
    }
    std::cout << "+" << std::endl;

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            std::cout << "| " << board[i][j] << " ";
        }
        std::cout << "|" << std::endl;
        for (int k = 0; k < board.size(); k++) {
            std::cout << "+---";
        }
        std::cout << "+" << std::endl;
    }

}

/*
 * Private Function: askBoggleSize
 * Usage: askBoggleSize()
 * -------------------------------
 * Resizes the grid representing the board to appropriate
 * size, either 4x4 boggle or 5x5 boggle.
 */
void Boggle::askBoardSize() {
    system(kClearCommand.c_str());
    std::cout << "You can choose standard Boggle (4x4 grid)" << std::endl;
    std::cout << "or Big Boggle (5x5 grid)." << std::endl;

    /* Resize according to user preferences */
    std::string answer;
    size_t size;
    while (true) {
        std::cout << "Would you like Big Boggle? ";
        getline(std::cin, answer);
        if (toLowerCase(answer) == "yes") {
            size = kBigBoggleSize;
            break;
        }
        if (toLowerCase(answer) == "no") {
            size = kRegularBoggleSize;
            break;
        }
        std::cout << "Please answer yes or no." << std::endl;
    }

    board.resize(size, std::vector<char>(size));
}

void Boggle::setBoardCharacters() {
    std::cout << "I'll give you a chance to set up the board to your specification, \n"
            "which makes it easier to confirm your boggle program is working." << std::endl;

    std::string answer;
    bool forceConfiguration;
    while (true) {
        std::cout << "Do you want to force the board configuration?: ";
        getline(std::cin, answer);

        if (toLowerCase(answer) == "yes") {
            forceConfiguration = true;
            break;
        }

        if (toLowerCase(answer) == "no") {
            forceConfiguration = false;
            break;
        }

        std::cout << "Please answer yes or no." << std::endl;
    }

    if (forceConfiguration) { // Take input from user
        setUserString();
    } else { // Set boggle board by using random cubes
        setComputerGeneratedBoard();
    }
}

/*
 * Private Function: setUserString
 * Usage: setUserString()
 * -------------------------------
 * Asks the user for a string to fill the board
 */
void Boggle::setUserString() {
    int size = board.size();
    int gridSize = size * size;
    std::cout << "Enter a " << gridSize <<  " letter string to identify which letters you want on the cubes." << std::endl << std::endl;
    std::cout << "The first " << size << " letters are the cubes on the top row from left to"
            " right, the next " << size << " letters are on the second row and so on." << std::endl << std::endl;

    std::string boggleString;
    while (true) {
        std::cout << "Enter the string: ";
        getline(std::cin, boggleString);
        if (boggleString.size() >= gridSize) break;
        std::cout << "String must include "<< gridSize << " characters! Try again: ";
    }

    for (int i = 0; i < boggleString.size(); i++) {
        int row = i / size;
        int col = i % size;

        board[row][col] = boggleString[i];
    }
}

void Boggle::setComputerGeneratedBoard() {

}

void Boggle::fillBoard() {

}

void Boggle::showScore() const {

}

void Boggle::announceResult() const {

}

const std::string Boggle::STANDARD_CUBES[16] = {
        "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
        "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
        "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
        "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const std::string Boggle::BIG_BOGGLE_CUBES[25] =  {
        "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
        "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
        "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
        "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
        "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Mac OS X clear command */
const std::string Boggle::kClearCommand = "clear";

const size_t Boggle::kRegularBoggleSize = 4;
const size_t Boggle::kBigBoggleSize = 5;