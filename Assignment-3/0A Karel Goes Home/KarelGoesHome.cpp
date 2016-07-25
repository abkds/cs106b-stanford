/*
 * File: KarelGoesHome.cpp
 * ----------------------
 * This file is the starter project for the Karel Goes Home
 * warmup problem for Assignment 3
 */

#include <iostream>
#include "simpio.h"

/* Given a street number and avenue number, which are 1-indexed,
 * returns the number of paths Karel can take back home that only
 * moves left or down.
 */
int numPathsHome(int street, int avenue);

int main() {
	int street, avenue;

	street = getInteger("Enter the street number: ");
	avenue = getInteger("Enter the avenue number: ");

	std::cout << "Number of optimal paths to take back home: " <<
		numPathsHome(street, avenue) << std::endl;

	return 0;
}

/* Function: numPathsHome
 * Usage: numPaths = numPathsHome(3, 3);
 * -------------------------------------
 * Returns the number of paths Karel can take back home, from a
 * particular (street, avenue). The total number of optimal paths
 * from a location is the sum of the paths that can be taken from
 * taking a step left, or taking a step south.
 *
 * Base case is the location, where to reach because, there is only
 * single way to reach.
 */
int numPathsHome(int street, int avenue) {
	if (street == 1 && avenue == 1) return 1;
	else if (street < 0 || avenue < 0) return 0;
	else return numPathsHome(street-1, avenue) + numPathsHome(street, avenue-1);
}
