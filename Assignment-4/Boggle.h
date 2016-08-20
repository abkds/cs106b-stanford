//
// Created by Abhishek K Das on 20 August 2016
//

#ifndef _boggle_h
#define _boggle_h
#include <vector>
#include <string>
#include <set>

class Boggle {
public:
    /*
     * Constructor: Boggle
     * -------------------
     * Gives the user instructions and initializes all the book
     * keeping data members.
     */
    Boggle();

    void play();

private:
    /* Utility functions */
    void drawBoard() const;
    void giveInstructions() const;
    void welcome() const;
    void askBoardSize();
    void setBoardCharacters();
    void fillBoard();
    void showScore() const;
    void announceResult() const;
    void loadLexicon();
    void setUserString();
    void setComputerGeneratedBoard();

    /* Characters stored in row major order */
    std::vector<std::vector<char> > board;

    /* Words humans recognized */
    std::vector<std::string> wordsByHuman;

    /* Words computer recognized */
    std::vector<std::string> wordsByComputer;

    /* Lexicon */
    std::set<std::string> lexicon;

    /* Boggle cubes to initiate board */
    static const std::string STANDARD_CUBES[16];
    static const std::string BIG_BOGGLE_CUBES[25];
    static const std::string kClearCommand;
    static const size_t kRegularBoggleSize;
    static const size_t kBigBoggleSize;
};

#endif
