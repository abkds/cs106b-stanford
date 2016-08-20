/*
 * File: random.h
 * --------------
 * Interface for randomInteger function.
 * Taken from StanfordCPPLib.
 *
 */

#ifndef _random_h
#define _random_h
#include <vector>
/*
 * Function: randomInteger
 * Usage: int n = randomInteger(low, high);
 * ----------------------------------------
 * Returns a random integer in the range <code>low</code> to
 * <code>high</code>, inclusive.
 */

int randomInteger(int low, int high);

/*
 * Function: randomShuffle
 * Usage: randomShuffle(vec);
 * --------------------------
 * Randomly shuffles a vector
 */
template <typename T>
void randomShuffle(std::vector<T>& vec);

/*
 * Function: setRandomSeed
 * Usage: setRandomSeed(seed);
 * ---------------------------
 * Sets the internal random number seed to the specified value.  You
 * can use this function to set a specific starting point for the
 * pseudorandom sequence or to ensure that program behavior is
 * repeatable during the debugging phase.
 */

void setRandomSeed(int seed);

/*
 * Implementation notes: randomShuffle
 * -----------------------------------
 * Uses the Fisher-Yates algorithm to randomly shuffle a vector.
 */
template <typename T>
void randomShuffle(std::vector<T>& vec) {
    int size = vec.size();
    for (int i = 0; i < size; i++) {
        int r = randomInteger(i, size-1);
        std::swap(vec[i], vec[r]);
    }
}

#endif
