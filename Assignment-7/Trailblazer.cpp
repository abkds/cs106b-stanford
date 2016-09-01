/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include <limits>
using namespace std;

/* Function: shortestPath
 *
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc>
shortestPath(Loc start,
             Loc end,
             Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
             double heuristic(Loc start, Loc end, Grid<double>& world)) {

    Grid<BookKeep> bookKeepGrid(world.numRows(), world.numCols());

	shortestPathUtility(start, end, world, costFn, heuristic, bookKeepGrid);

    Vector<Loc> reversePath;
    /* Reconstruct path */
    while (end != NIL) {
        reversePath.push_back(end);
        end = bookKeepGrid[end.row][end.col].parent;
    }

    Vector<Loc> path;
    for (int i = reversePath.size() - 1; i >= 0; i--) {
        path.push_back(reversePath[i]);
    }

    return path;
}

Set<Edge> createMaze(int numRows, int numCols) {
	// TODO: Fill this in!
	error("createMaze is not implemented yet.");
    return Set<Edge>();
}

/* Implementation notes:
 *
 * Uses Dijkstra algorithm to find the shortest path between two pair of points
 * start and end. Keeps track of the book keeping variables in a grid of BookKeep
 * cells.
 */
void
shortestPathUtility(Loc start,
             Loc end,
             Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
             double heuristic(Loc start, Loc end, Grid<double>& world),
             Grid<BookKeep>& bookKeepGrid) {

    /* Mark all nodes gray */
    for (int i = 0; i < bookKeepGrid.numRows(); i++) {
        for (int j = 0; j < bookKeepGrid.numCols(); j++) {
            bookKeepGrid[i][j].color = GRAY;
            bookKeepGrid[i][j].distance = numeric_limits<double>::infinity();
            bookKeepGrid[i][j].parent = NIL;
        }
    }

    /* Mark initial node start as yellow and distance 0 */
    bookKeepGrid[start.row][start.col].color = YELLOW;
    bookKeepGrid[start.row][start.col].distance = heuristic(start, end, world);

    /* Enqueue start into priority queue with priority 0 */
    TrailblazerPQueue<Loc> pq;
    pq.enqueue(start, 0);

    Loc u = start;

    while (true) {
        u = pq.dequeueMin();
        bookKeepGrid[u.row][u.col].color = GREEN;
        colorCell(world, u, GREEN);

        if (u == end) return;

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
				Loc v = makeLoc(u.row + i, u.col + j);
                if (world.inBounds(v.row, v.col) && v != u) {

                    if (bookKeepGrid[v.row][v.col].color == GRAY) {
                        bookKeepGrid[v.row][v.col].color = YELLOW;
                        colorCell(world, v, YELLOW);
                        bookKeepGrid[v.row][v.col].distance =
                            bookKeepGrid[v.row][v.col].distance +
                            costFn(u, v, world);
                        bookKeepGrid[v.row][v.col].parent = u;
                        pq.enqueue(v,
                            bookKeepGrid[v.row][v.col].distance +
                            costFn(u, v, world) + heuristic(v, end, world)
                        );
                    }

                    if ((bookKeepGrid[v.row][v.col].color == YELLOW) &&
                        (bookKeepGrid[v.row][v.col].distance >
                            costFn(u, v, world) + bookKeepGrid[u.row][u.col].distance)) {

                        bookKeepGrid[v.row][v.col].distance =
                            costFn(u, v, world) + bookKeepGrid[u.row][u.col].distance;
                        bookKeepGrid[v.row][v.col].parent = u;
                        pq.decreaseKey(v,
                            costFn(u, v, world) +
                            bookKeepGrid[u.row][u.col].distance +
                            heuristic(v, end, world)
                        );
                    }
                }
            }
        }
    }

}
