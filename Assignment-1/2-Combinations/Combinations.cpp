/*
 * File: Combinations.cpp
 * ----------------------
 * Name: Abhishek K Das
 *
 * This program demonstrates a recursive of implmentation of n choose k
 * function.
 */

#include <iostream>
#include "simpio.h"

/*
 * Function: choose
 * Usage: int m = choose(n, k)
 * ---------------------------
 * This function calculates the value of combinatarial choose function, by a
 * recursive strategy. It uses the insight provided by Pascal triangle.
 *                         1
 *                       1   1
 *                     1   2   1
 *                   1   3   3   1
 *                 1   4   6   4   1
 *               1   5  10  10   5   1
 *
 * As can be seen from the Pascal triangle, except for the edges in the row,
 * (which are 1 always) the numbers in the middle are a sum of two numbers
 * in the row above which are just right and left to it, in the upper row.
 */
int choose(int n, int k);

int main() {
    std::cout << "Calculate the value of n choose k." << std::endl;

    int n = getInteger("Enter the value of n: ");
    int k = getInteger("Enter the value of k: ");

    std::cout << "The value of choose(n, k) is " << choose(n, k) << std::endl;
    return 0;
}

int choose(int n, int k) {
    if (k == 0 || k == n) return 1;
    else return choose(n-1, k-1) + choose(n-1, k);
}
