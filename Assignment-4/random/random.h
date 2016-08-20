/*
 * File: random.h
 * --------------
 * Interface for randomInteger function.
 * Taken from StanfordCPPLib.
 *
 */

#ifndef _random_h
#define _random_h

/*
 * Function: randomInteger
 * Usage: int n = randomInteger(low, high);
 * ----------------------------------------
 * Returns a random integer in the range <code>low</code> to
 * <code>high</code>, inclusive.
 */

int randomInteger(int low, int high);

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

#endif
