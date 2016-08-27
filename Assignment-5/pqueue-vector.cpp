/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */

#include "pqueue-vector.h"
#include <vector>
#include <string>
#include <algorithm>
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
    // Do nothing, STL vector is initialized automatically
}

VectorPriorityQueue::~VectorPriorityQueue() {
    // Do nothing, STL vector is destructed automatically
}

int VectorPriorityQueue::size() {
    return priorityQueue.size();
}

bool VectorPriorityQueue::isEmpty() {
    return priorityQueue.empty();
}

void VectorPriorityQueue::enqueue(std::string value) {
    priorityQueue.push_back(value);
}

std::string VectorPriorityQueue::peek() {
    if (size() == 0) error("peek: Attempting to peek at an empty queue");
    std::vector<std::string>::iterator minIt =
            std::min_element(priorityQueue.begin(), priorityQueue.end());

    return *minIt;
}

std::string VectorPriorityQueue::dequeueMin() {
    if (size() == 0) error("dequeueMin: Attempting to dequeue an empty queue");

    std::vector<std::string>::iterator minIt =
            std::min_element(priorityQueue.begin(), priorityQueue.end());

    std::string value = *minIt;

    priorityQueue.erase(minIt);

    return value;
}
