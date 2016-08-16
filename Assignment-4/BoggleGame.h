/*
 * BoggleGame.h
 * ------------
 * This file is an interface for playing a game of Boggle between
 * human and computer.
 */
#ifndef _BoggleGame_Defined
#define _BoggleGame_Defined

#include <string>
#include "StanfordCPPLib/grid.h"

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

class BoggleGame {
public:
    /*
     * Function: initBoard()
     * Usage: BoggleGame.initBoard()
     * -----------------------------
     * Initializes the board with a set of cubes for a game of Boggle.
     * User can either provide a set of Boggle Cubes, or it will be initialize
     * with a given set of cubes
     */
    void initBoard();
private:
    Grid<std::string> boggleGrid;

    /* Constants */
    static const string STANDARD_CUBES[16];
    static const string BIG_BOGGLE_CUBES[25];
    static const int BOGGLE_WINDOW_WIDTH = 650;
    static const int BOGGLE_WINDOW_HEIGHT = 350;
};

#endif
