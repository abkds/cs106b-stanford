/*
 * File: Sierpinski.cpp
 * ----------------------
 * This file is the starter project for the Sierpinski Triangle problem
 * on Assignment #3.
 */

#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "random.h"
using namespace std;

const double ORDER = 5;

/* Function prototype */
void subdivideTriangle(GWindow& gw, GPoint p1, GPoint p2, GPoint p3, int order);

GPoint midPoint(GPoint& p1, GPoint& p2);

double distance(GPoint& p1, GPoint& p2);

/* Main program */
int main() {
	GWindow gw;

	/* Equilateral triangle */
	GPoint p1(150, 220);
	GPoint p2 = gw.drawPolarLine(p1, 200, 0);
	GPoint p3 = gw.drawPolarLine(p2, 200, 120);
	gw.drawPolarLine(p3, 200, -120);

	subdivideTriangle(gw, p1, p2, p3, ORDER);

	return 0;
}


/*
 * Function: midPoint
 * Usage: p3 = midPoint(p1, p2);
 * -----------------------------
 * Returns the mid point between the line joining p1 and p2.
 */
GPoint midPoint(GPoint& p1, GPoint& p2) {
	GPoint mid((p1.getX() + p2.getX()) / 2, (p1.getY() + p2.getY())/2 );
	return mid;
}

/*
 * Function: distance
 * Usage: d = distance(p1, p2);
 * ----------------------------
 * Returns the distance between two points.
 */
double distance(GPoint& p1, GPoint& p2) {
	return sqrt(pow( p1.getX() - p2.getX() , 2) + pow(p1.getY() - p2.getY(), 2));
}

/*
 * Function: subdivideTriangle
 * Usage: subdivideTriangle(gw, p1, p2, p3);
 * -----------------------------------------
 * Subdivides a triangle recursively into 4 triangles by explicity making
 * 3 triangles (one triangle is formed because it is sandwiched between
 * the other 3), then recurses into each of the new triangle formed.
 *
 * Such a recursive triangle structure is known as Sierpinski triangle.
 * The order of recursion (the number of triangle is to be subdivided) is
 * passed.
 */
void subdivideTriangle(GWindow& gw, GPoint p1, GPoint p2, GPoint p3, int order) {

	if (order == 0) return;

	GPoint p12 = midPoint(p1, p2);
	GPoint p23 = midPoint(p2, p3);
	GPoint p31 = midPoint(p3, p1);

	gw.drawLine(p12, p23);
	gw.drawLine(p23, p31);
	gw.drawLine(p31, p12);

	subdivideTriangle(gw, p1, p12, p31, order-1);
	subdivideTriangle(gw, p12, p2, p23, order-1);
	subdivideTriangle(gw, p31, p23, p3, order-1);
}
