/**********************************************
 * File: pqueue-heap.h
 *
 * A priority queue class backed by a binary
 * heap.
 */
#ifndef PQueue_Heap_Included
#define PQueue_Heap_Included

#include <string>

using namespace std;

/* A class representing a priority queue backed by an
 * binary heap.
 */
class HeapPriorityQueue {
public:
    /* Constructs a new, empty priority queue backed by a binary heap. */
    HeapPriorityQueue();

    /* Cleans up all memory allocated by this priority queue. */
    ~HeapPriorityQueue();

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
    static const int INITIAL_CAPACITY = 10;

    /*
     * Expands the capacity of heap if there is no more space.
     */
    void expandCapacity();

    /*
     * Heap is stored as a dynamic array with indexing starting from 1.
     * Element 0 has dummy value and is ignored throughout.
     */
    string *heap;

    int count;
    int capacity;

    /*
     * Bubbles down the element at top after dequeue the minimum.
     *
     * Last element in the heap is moved to top after removing the minimum
     * element. To restore the binary heap property, it is necessary to move
     * the element at top to appropriate position in heap.
     */
    void bubbleDown(int index);

    /*
     * Bubbles up a newly inserted element.
     *
     * When a new element is inserted it may disturb the heap property,
     * to restore the property, it is moved to the appropriate place.
     */
    void bubbleUp(int index);
};

#endif
