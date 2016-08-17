//
// Created by Abhishek K Das on 16/08/16.
//

#include "BoggleGame.h"
#include "StanfordCPPLib/strlib.h"
#include "StanfordCPPLib/simpio.h"
#include "gboggle.h"
#include "StanfordCPPLib/gwindow.h"
#include <string>

void BoggleGame::printInstructions() {
    welcome();
    if (askUntilYesOrNo("Do you need instructions? ")) {
        giveInstructions();
    }
}

void BoggleGame::initBoard() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);

    std::cout << "You can choose standard Boggle (4x4 grid)" << std::endl;
    std::cout << "or Big Boggle (5x5 grid)." << std::endl;

    /* Resize according to user preferences */
    if (askUntilYesOrNo("Would you like Big Boggle? ")) {
        boggleGrid.resize(5, 5);
        drawBoard(5, 5);
    } else {
        boggleGrid.resize(4, 4);
        drawBoard(4, 4);
    }

    std::cout << "I'll give you a chance to set up the board to your specification, which makes "
            "it easier to confirm your boggle program is working." << std::endl;

    if (askUntilYesOrNo("Do you want to force the board configuration? ")) {
        int gridSize = boggleGrid.numCols() * boggleGrid.numCols();
        int colSize = boggleGrid.numCols();
        int rowSize = boggleGrid.numRows();

        std::cout << "Enter a " << gridSize <<  " letter string to identify which letters you want on the cubes." << std::endl;
        std::cout << "The first " << colSize << " letters are the cubes on the top row from left to"
                " right, the next " << colSize << " letters are on the second row and so on." << std::endl;

        std::string boggleString = getLine("Enter the string: ");

        while (true) {
            if (boggleString.size() >= gridSize) {
                boggleString = toUpperCase(boggleString);
                boggleString = boggleString.substr(0, gridSize);
                break;
            } else {
                std::string question = "String must include " + integerToString(gridSize) + " characters. Try again: ";
                boggleString = getLine(question);
            }
        }

        for (int i = 0; i < boggleString.size(); i++) {
            int row = i / rowSize;
            int col = i % rowSize;

            boggleGrid[row][col] = boggleString[i];
            labelCube(row, col, boggleString[i]);
        }

    } else {
        // Fill the cubes randomly
    }

    // Ok, take all the time you want and find all the words you can!  Signal that you're finished by entering an empty line.

}

const string BoggleGame::STANDARD_CUBES[16] = {
        "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
        "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
        "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
        "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const string BoggleGame::BIG_BOGGLE_CUBES[25] =  {
        "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
        "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
        "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
        "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
        "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */
void BoggleGame::welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the gloomy instructions for the user.
 */
void BoggleGame::giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

/*
 * Function: askUntilYesOrNo
 * Usage: if (askUntilYesOrNo("Do you need instructions? ")) ...
 * -------------------------------------------------------------
 * Repeatedly asks a question until the user answers a question
 * with yes or no correctly.
 */
bool BoggleGame::askUntilYesOrNo(std::string question) {
    string answer = getLine(question);

    while (true) {
        if (toLowerCase(answer) == "yes") {
            return true;
        }

        if (toLowerCase(answer) == "no") {
            return false;
        }

        std::cout << "Please enter yes or no." << std::endl;
        answer = getLine(question);
    }
}