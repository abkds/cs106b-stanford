/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: Abhishek K Das
 *
 * This program simulates flipping of coins according to a given
 * probability and stops and when a fixed number of heads occur
 * consecutively.
 */

#include <iostream>
#include <string>
//#include "console.h"
#include "random.h"


/* Number of heads to occur consecutively */
const int N_HEADS = 3;

/* Probability of heads */
const double P = 0.5;

/*
 * Function: SimulateCoinFlipping
 * Usage: int n = SimulateCoinFlipping()
 * -----------------------------
 * This function simulates a run of coin flipping. Coins are flipped
 * according to a given probability consecutively until and unless a
 * fixed number of consecutive heads occur. The function stops and exits
 * when it happens. It returns the number of trials required for the
 * event to occur.
 */
int SimulateCoinFlipping();

int main() {
    int n = SimulateCoinFlipping();

    std::cout << "It took " << n << " flips to get " << N_HEADS
        << " consecutive heads." << std::endl;

    return 0;
}

int SimulateCoinFlipping() {

    int totalTrials = 0;
    int consecutiveHeads = 0;

    while (true) {
        totalTrials++;
        if (randomChance(P)) {
            std::cout << "heads" << std::endl;
            consecutiveHeads++;

            /* Break when required number of consecutive heads occur. */
            if (consecutiveHeads == N_HEADS) break;

        } else {
            std::cout << "tails" << std::endl;
            consecutiveHeads = 0;
        }
    }

    return totalTrials;
}
