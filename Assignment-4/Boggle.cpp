/*
 * File: Boggle.cpp
 * ----------------
 * This file is the main starter file for Assignment #4, Boggle.
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
#include "BoggleGame.h"
using namespace std;



/* Function prototypes */

void welcome();
void giveInstructions();

/* Main program */

int main() {
    BoggleGame boggleGame;
    boggleGame.printInstructions();
    boggleGame.initBoard();
    return 0;
}

// [TODO: Fill in the rest of the code]
