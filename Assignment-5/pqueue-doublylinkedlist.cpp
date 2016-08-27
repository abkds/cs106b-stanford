/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */

#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
    head = NULL;
    count = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
    Cell *cp = head;

    while (cp != NULL) {
        Cell *oldCp = cp;
        cp = cp->next;
        delete oldCp;
    }
}

int DoublyLinkedListPriorityQueue::size() {
    return count;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
    return count == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
    Cell *cp = new Cell;
    cp->value = value;
    cp->prev = NULL;

    if (head == NULL) {
        cp->next = NULL;
    } else {
        cp->next = head;
        cp->next->prev = cp;
    }
    head = cp;
    count++;
}

string DoublyLinkedListPriorityQueue::peek() {
    if (count == 0) error("peek: Attempting to peek an empty queue");

    Cell *cp = head;
    string minValue = head->value;

    while (cp != NULL) {
        if (cp->value < minValue) {
            minValue = cp->value;
        }
        cp = cp->next;
    }

    return minValue;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
    if (count == 0) error("dequeueMin: Attempting to dequeue an empty queue");
    string value = peek();

    Cell *cp = head;
    while (cp->value != value) {
        cp = cp->next;
    }
    if (cp->next == NULL && cp->prev == NULL) {
        head = NULL;
    } else if (cp->next == NULL && cp->prev != NULL) {
        cp->prev->next = NULL;
    } else if (cp->next != NULL && cp->prev == NULL) {
        head = cp->next;
        head->prev = NULL;
    } else {
        cp->prev->next = cp->next;
        cp->next->prev = cp->prev;
    }

    count--;
    delete cp;
    return value;
}
