/*
 * File: random.cpp
 * ----------------
 * Implementation for random.h interface.
 * Taken from StanfordCPPLib.
 */

#include <cstdlib>
#include <cmath>
#include <ctime>
#include "random.h"
#include "private/randompatch.h"

/* Private function prototype */
static void initRandomSeed();

int randomInteger(int low, int high) {
    initRandomSeed();
    double d = rand() / (double(RAND_MAX) + 1);
    double s = d * (double(high) - low + 1);
    return int(floor(low + s));
}

/*
 * Implementation notes: setRandomSeed
 * -----------------------------------
 * The setRandomSeed function simply forwards its argument to srand.
 * The call to initRandomSeed is required to set the initialized flag.
 */

void setRandomSeed(int seed) {
    initRandomSeed();
    srand(seed);
}

/*
 * Implementation notes: initRandomSeed
 * ------------------------------------
 * The initRandomSeed function declares a static variable that keeps track
 * of whether the seed has been initialized.  The first time initRandomSeed
 * is called, initialized is false, so the seed is set to the current time.
 */

static void initRandomSeed() {
    static bool initialized = false;
    if (!initialized) {
        srand(int(time(NULL)));
        initialized = true;
    }
}
