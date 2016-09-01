/******************************************************************************
 * File: Trailblazer.h
 *
 * Exports functions that use Dijkstra's algorithm, A* search, and Kruskal's
 * algorithm as specified in the assignment handout.
 */

#ifndef Trailblazer_Included
#define Trailblazer_Included

#include "TrailblazerTypes.h"
#include "StanfordCPPLib/set.h"
#include "StanfordCPPLib/grid.h"

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
 * search.  Make sure to update both this function prototype and the
 * implementation inside of Trailblazer.cpp.
 */
Vector<Loc>
shortestPath(Loc start,
             Loc end,
             Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
             double heuristic(Loc start, Loc end, Grid<double>& world));

/* Function: createMaze
 *
 * Creates a maze of the specified dimensions using a randomized version of
 * Kruskal's algorithm, then returns a set of all of the edges in the maze.
 *
 * As specified in the assignment handout, the edges you should return here
 * represent the connections between locations in the graph that are passable.
 * Our provided starter code will then use these edges to build up a Grid
 * representation of the maze.
 */
Set<Edge> createMaze(int numRows, int numCols);

/* Type: BookKeep
 *
 * A type representing bookkeeping variables for a location, as encoded by its
 * shortest distance (found by Search algorithm), it's parent cell (helps in
 * reconstructing the path) and the color of the node when the search advances.
 */
struct BookKeep {
    double distance;
    Loc parent;
    Color color;
};

/* Function: shortestPathUtility
 *
 * Utility function to find the shortest path distance between start and end
 * locations in a grid. Helps in maintaining book keeping variables to reconstruct
 * path and maintain state during execution of search algorithm
 */
void
shortestPathUtility(Loc start,
                    Loc end,
                    Grid<double>& world,
                    double costFn(Loc from, Loc to, Grid<double>& world),
                    double heuristic(Loc start, Loc end, Grid<double>& world),
                    Grid<BookKeep>& bookKeepGrid);

/* Constant: NIL
 *
 * A sentinel location, which helps as a stopping point while constructing
 * the path from the optimal solution provided by the search algorithm.
 */
static const Loc NIL = makeLoc(-1, -1);

#endif
