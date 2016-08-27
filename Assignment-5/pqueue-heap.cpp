/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */

#include <algorithm>
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
    capacity = INITIAL_CAPACITY;
    heap = new string[capacity];
    count = 0;
}

HeapPriorityQueue::~HeapPriorityQueue() {
    delete[] heap;
}

int HeapPriorityQueue::size() {
    return count;
}

bool HeapPriorityQueue::isEmpty() {
    return count == 0;
}

void HeapPriorityQueue::enqueue(string value) {
    if (count == capacity - 1) {
        expandCapacity();
    }
    heap[++count] = value;
    bubbleUp(count);
}

/*
 * Top most position contains the smallest element by heap property
 */
string HeapPriorityQueue::peek() {
    if (isEmpty()) error("peek: Attempting to peek an empty queue");
    return heap[1];
}

string HeapPriorityQueue::dequeueMin() {
    if (isEmpty()) error("dequeueMin: Attempting to dequeue an empty queue");
    string minValue = peek();
    heap[1] = heap[count--];
    bubbleDown(1);
    return minValue;
}

void HeapPriorityQueue::expandCapacity() {
    string *oldHeap = heap;
    capacity = 2 * capacity;
    heap = new string[capacity];

    for (int i = 1; i <= count; i++) {
        heap[i] = oldHeap[i];
    }

    delete[] oldHeap;
}

void HeapPriorityQueue::bubbleUp(int index) {
    if (index <= 1) return;

    int parentIndex = index / 2;

    if (heap[parentIndex] > heap[index]) {
        std::swap(heap[parentIndex], heap[index]);
        bubbleUp(parentIndex);
    }
}

void HeapPriorityQueue::bubbleDown(int index) {
    int leftIndex = 2 * index;
    int rightIndex = 2 * index + 1;

    if (leftIndex <= count && rightIndex <= count) {
        int minIndex;

        if (heap[leftIndex] < heap[rightIndex]) minIndex = leftIndex;
        else minIndex = rightIndex;

        if (heap[index] > heap[minIndex]) {
            std::swap(heap[index], heap[minIndex]);
            bubbleDown(minIndex);
        }
    }

    if (leftIndex <= count) {
        if (heap[index] > heap[leftIndex]) {
            std::swap(heap[index], heap[leftIndex]);
        }
    }

}
