/*
 * File: Boggle.cpp
 * ----------------
 * Implementation file for Boggle Game
 * Author: Abhishek K Das
 */

#include "Boggle.h"
#include "StanfordCPPlib/strlib.h"
#include "StanfordCPPlib/random.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <set>
#include <fstream>
#include <cstdlib>

Lexicon Boggle::lexicon;

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
    Boggle::lexicon.addWordsFromFile("EnglishWords.txt");
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
    system(kClearCommand.c_str());
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
    used.resize(size, std::vector<bool>(size));
}

/*
 * Private Function: setBoardCharacters
 * Usage: setBoardCharacters()
 * ------------------------------------
 * Configures the board and sets the data member board.
 */
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

    boggleString = toUpperCase(boggleString);

    for (int i = 0; i < boggleString.size(); i++) {
        int row = i / size;
        int col = i % size;

        board[row][col] = boggleString[i];
    }
}

void Boggle::setComputerGeneratedBoard() {
    std::vector<std::string> cubes;
    int size = board.size();

    /* Copy the cubes into a vector string to shuffle */
    if (board.size() == kRegularBoggleSize) {
        std::copy(STANDARD_CUBES, STANDARD_CUBES + sizeof(STANDARD_CUBES) / sizeof(STANDARD_CUBES[0]),
                  std::back_inserter(cubes));
    }

    if (board.size() == kBigBoggleSize) {
        std::copy(BIG_BOGGLE_CUBES, BIG_BOGGLE_CUBES + sizeof(BIG_BOGGLE_CUBES) / sizeof(BIG_BOGGLE_CUBES[0]),
                  std::back_inserter(cubes));
    }

    randomShuffle(cubes);

    for (int i = 0; i < cubes.size(); i++) {
        int row = i / size;
        int col = i % size;

        board[row][col] = cubes[i][randomInteger(0, 5)];
    }
}

void Boggle::play() {
    humanTurn();
    computerTurn();
}
/*
 * Private Function: humanTurn
 * Usage: humanTurn()
 * ---------------------------
 * Allows human to find words on the board, checks
 * whether the word entered is correct if correct adds
 * it to the number of valid words entered by human.
 */
void Boggle::humanTurn() {

    std::cout << std::endl << std::endl;

    std::cout << "Ok, take all the time you want and find all the words you can! Signal\n"
            "that you're finished by entering an empty line." << std::endl;

    std::string word;
    std::cout << "Enter a word: ";
    while (getline(std::cin, word)) {

        if (word.size() == 0) break;

        if (isValidWord(toUpperCase(word))) {
            auto it = std::find(wordsByHuman.begin(), wordsByHuman.end(), word);
            if (it == wordsByHuman.end()) {
                wordsByHuman.push_back(word);
                drawBoard();
                std::cout << "Ok, take all the time you want and find all the words you can! Signal\n"
                "that you're finished by entering an empty line." << std::endl;
                showScore();
            } else {
                std::cout << "You've already guessed that!" << std::endl;
            }
        }
        std::cout << "Enter a word: ";
    }
}


void Boggle::computerTurn() {
    int size = board.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::string start;
            start += board[i][j];
            resetUsed();
            used[i][j] = true;
            findWords(start, i, j);
        }
    }

    drawBoard();
    showScore();
}


/*
 * Function: findWords
 * Usage: findWords(start, i, j)
 * -----------------------------
 * Exhaustively searches the entire board for all words starting from
 * row, col. Uses backtracking for the words. Prunes the search if the
 * word till now is not a valid prefix in the lexicon.
 *
 * Note: tillNow is automatically backtracked since it is passed as a
 * copied variable.
 */
void Boggle::findWords(std::string& tillNow, int& row, int& col) {


    if (lexicon.contains(tillNow) && tillNow.size() >= kMinWordLength) {
        if (std::find(wordsByComputer.begin(), wordsByComputer.end(), tillNow) == wordsByComputer.end())
            wordsByComputer.push_back(tillNow);
    }

    if (!lexicon.containsPrefix(tillNow)) return;

    for (int i = 0; i < dp.size(); i++) {
        row += dp[i].first;
        col += dp[i].second;

        if (inBounds(row, col) && !used[row][col]) {
            // make move
            used[row][col] = true;
            tillNow.push_back(board[row][col]);

            findWords(tillNow, row, col);

            // backtrack
            tillNow.pop_back();
            used[row][col] = false;
        }

        row -= dp[i].first;
        col -= dp[i].second;
    }
}

/*
 * Validates whether the word entered is valid for the
 * given board, and exists in the lexicon.
 */
bool Boggle::isValidWord(std::string word) {
    resetUsed();
    if (word.size() < 4) {
        std::cout << "That word doesn't meet the minimum word length." << std::endl;
        return false;
    }

    int size = board.size();

    bool onBoard = false;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (word[0] == board[i][j]) {
                used[i][j] = true;
                if (isWordOnBoard(word, i, j)) {
                    onBoard = true;
                    break;
                }
            } else {
                resetUsed();
            }
        }
    }

    if (onBoard) {
        if (lexicon.contains(word)) {
            return true;
        } else {
            std::cout << "That's not a word" << std::endl;
            return false;
        }
    } else {
        std::cout << "You can't make that word!" << std::endl;
        return false;
    }

}

void Boggle::resetUsed() {
    for (auto it = used.begin(); it != used.end(); ++it) {
        std::fill(it->begin(), it->end(), false);
    }
}

/*
 * Function: isWordOnBoard
 * Usage: if (isWordOnBoard(word, 0, 1)) ...
 * ---------------------------------------------
 * Recursively validates whether a word can be constructed on board
 * following the rules of Boggle
 */
bool Boggle::isWordOnBoard(std::string word, int row, int col) {
    if (word.size() == 1 && word[0] == board[row][col]) return true;
    if (word[0] != board[row][col]) return false;

    int newRow;
    int newCol;

    for (int i = 0; i < dp.size(); i++) {
        newRow = row + dp[i].first;
        newCol = col + dp[i].second;

        if (inBounds(newRow, newCol) && !used[newRow][newCol]) {
            // make new move
            used[newRow][newCol] = true;

            if (isWordOnBoard(word.substr(1), newRow, newCol))
                return true;

            // backtrack
            used[newRow][newCol] = false;
        }
    }

    return false;

}

/*
 * Private Function: inBounds(int row, int col)
 * Usage: if (inBounds(row, col)) ...
 * --------------------------------------------
 * Checks whether the row, col is within the bounds
 * of the board
 */
bool Boggle::inBounds(int row, int col) const {
    int size = board.size();
    return (row >= 0) && (row < size)
            && (col >= 0) && (col < size);

}

void Boggle::showScore() const {
    std::cout << std::endl;

    std::cout << "Human\n";
    showScoreForPlayer(wordsByHuman);

    std::cout << std::endl << std::endl;
    std::cout << "-----------------------------" << std::endl << std::endl;

    std::cout << "Computer\n";
    showScoreForPlayer(wordsByComputer);

    std::cout << std::endl << std::endl;
    std::cout << "-----------------------------" << std::endl << std::endl;
}

/*
 * Function: calculateScore
 * Usage: score = calculateScore(words)
 * ------------------------------------
 * Given a vector of words calculates the score.
 * 4-letter: 1 point
 * 5-letter: 2 points
 * ...
 */
int Boggle::calculateScore(const std::vector<std::string>& vec) const {

    int score = 0;
    for (std::vector<std::string>::const_iterator it = vec.begin();
            it != vec.end(); ++it) {
        score += (it->size() - 3);
    }
    return score;
}

/*
 * Private Function: showScoreForPlayer
 * Usage: showScoreForPlayer()
 * ------------------------------------
 * Shows score and words for a single player.
 */
void Boggle::showScoreForPlayer(const std::vector<std::string>& words) const {
    std::cout << "Score: " << calculateScore(words) << std::endl;
    std::cout << "Words: ";

    for (int i = 0; i < words.size(); i++) {
        if (i % 10 == 0) {
            std::cout << std::endl;
        }
        std::cout << toLowerCase(words[i]) << "  ";
    }
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
