//
// Created by Abhishek K Das on 20 August 2016
//

#ifndef _boggle_h
#define _boggle_h
#include <vector>
#include <string>
#include "StanfordCPPlib/lexicon.h"

class Boggle {
public:
    /*
     * Constructor: Boggle
     * -------------------
     * Gives the user instructions and initializes all the book
     * keeping data members.
     */
    Boggle();

    /*
     * Simulate a single Boggle game between
     * human and computer.
     */
    void play();

private:
    /* Utility functions */
    void drawBoard() const;
    void giveInstructions() const;
    void welcome() const;
    void askBoardSize();
    void setBoardCharacters();
    void showScore() const;
    void loadLexicon();
    void setUserString();
    void setComputerGeneratedBoard();
    void humanTurn();
    void computerTurn();
    void showScoreForPlayer(const std::vector<std::string>& words) const;
    bool isValidWord(std::string word);
    bool isWordOnBoard(std::string word, int row, int col);
    bool inBounds(int row, int col) const;
    void resetUsed();
    int calculateScore(const std::vector<std::string>& vec) const;
    void findWords(std::string& tillNow, int& row, int& col);

    /* Characters stored in row major order */
    std::vector<std::vector<char> > board;
    std::vector<std::vector<bool> > used;

    /* Words humans recognized */
    std::vector<std::string> wordsByHuman;

    /* Words computer recognized */
    std::vector<std::string> wordsByComputer;

    /* Lexicon */
    static Lexicon lexicon;

    /* Constants */
    static const std::string STANDARD_CUBES[16];
    static const std::string BIG_BOGGLE_CUBES[25];
    const std::string kClearCommand = "clear";
    const size_t kRegularBoggleSize = 4;
    const size_t kBigBoggleSize = 5;
    const std::vector<std::pair<int, int> > dp = {
            std::make_pair(-1, -1), std::make_pair(-1, 0), std::make_pair(-1, 1),
            std::make_pair( 0, -1),                        std::make_pair( 0, 1),
            std::make_pair( 1, -1), std::make_pair( 1, 0), std::make_pair( 1, 1)
    };
    const int kMinWordLength = 4;
};

#endif
