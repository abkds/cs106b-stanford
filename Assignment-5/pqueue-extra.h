/**********************************************
 * File: pqueue-extra.h
 *
 * Your own custom priority queue class, if you
 * want to build one for extra credit.
 *
 * Please replace these file comments with a
 * description of how your priority queue works.
 */
#ifndef PQueue_Extra_Included
#define PQueue_Extra_Included

#include <string>
using namespace std;

struct Cell {
    Cell * parent, * sibling, * child;
    int degree;
    string key;
};

/* A class representing a priority queue backed by an
 * binomial heap.
 */
class ExtraPriorityQueue {
public:
    /* Constructs a new, empty priority queue. */
    ExtraPriorityQueue();

    /* Cleans up all memory allocated by this priority queue. */
    ~ExtraPriorityQueue();

    /* Returns the number of elements in the priority queue. */
    int size();

    /* Returns whether or not the priority queue is empty. */
    bool isEmpty();

    /* Enqueues a new string into the priority queue. */
    void enqueue(string value);

    /* Returns, but does not remove, the lexicographically first string in the
     * priority queue.
     */
    string peek();

    /* Returns and removes the lexicographically first string in the
     * priority queue.
     */
    string dequeueMin();

private:
    Cell * head;
    int count;

    /* Links to binomial tree of the same order.
     * This procedure is repeatedly used by the union procedure
     * to link together trees of same order
     */
    void binomialLink(Cell * & binomialTreeY, Cell * & binomialTreeZ);

    /* Merges two binomial heaps according to the degree of the
     * root nodes in both the heaps
     */
    Cell * binomialHeapMerge(Cell * & bHx, Cell * & bHy);

    /* Returns the union of merged binomial heaps.
     * Uses binomialHeapMerge as a subroutine
     */
    Cell * binomialHeapUnion(Cell * & bHx, Cell * & bHy);
};

#endif
