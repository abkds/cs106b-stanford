/*************************************************************
 * File: pqueue-extra.cpp
 *
 * Implementation file for the ExtraPriorityQueue class.  You
 * do not need to implement this class, but we're happy to
 * give you extra credit if you do!
 */

#include "pqueue-extra.h"
#include "error.h"

ExtraPriorityQueue::ExtraPriorityQueue() {
    head = NULL;
    count = 0;
}

ExtraPriorityQueue::~ExtraPriorityQueue() {
    while (!isEmpty()) {
        dequeueMin();
    }
}

int ExtraPriorityQueue::size() {
    return count;
}

bool ExtraPriorityQueue::isEmpty() {
    return count == 0;
}

void ExtraPriorityQueue::enqueue(string value) {
    Cell * cp = new Cell;
    cp->parent = NULL;
    cp->child = NULL;
    cp->sibling = NULL;
    cp->degree = 0;
    cp->key = value;

    head = binomialHeapUnion(head, cp);
    count++;
}

/*
 * In a binomial heap, following its properties, the root
 * node should list should contain the minimum. Since for n
 * elements there are at max log n trees and hence log n nodes
 *
 * This operation takes O(log n) time.
 */
string ExtraPriorityQueue::peek() {
    if (isEmpty()) error("peek: Attempting to peek an empty queue");
    string minKey = head->key;

    Cell * cp = head;

    while (cp != NULL) {
        if (cp->key < minKey) {
            minKey = cp->key;
        }
        cp = cp->sibling;
    }

    return minKey;
}

string ExtraPriorityQueue::dequeueMin() {
    if (isEmpty()) error("dequeueMin: Attempting to dequeue an empty queue");
    string minKey = peek();

    Cell ** pCp = &head;
    while ((*pCp)->key != minKey) {
        pCp = &((*pCp)->sibling);
    }

    Cell * minNodeHead = *pCp;
    *pCp = (*pCp)->sibling;

    // head contains the original heap - tree of min node
    // Min Node head points to tree of minimum node

    // Reverse the sibling pointers of children nodes
    Cell * head_;
    if (minNodeHead->degree == 0) {
        head_ = NULL;
    } else {
        Cell * minNodeChild = minNodeHead->child;
        Cell * cp = minNodeChild;

        head_ = new Cell;
        head_->parent = NULL;
        head_->sibling = NULL;
        head_->key = cp->key;
        head_->child = cp->child;
        head_->degree = cp->degree;

        Cell * oldCp = cp;
        cp = cp->sibling;
        delete oldCp;

        while (cp != NULL) {
            Cell * newCell = new Cell;
            newCell->sibling = head_;
            newCell->parent = NULL;
            newCell->key = cp->key;
            newCell->child = cp->child;
            newCell->degree = cp->degree;
            head_ = newCell;
            oldCp = cp;
            cp = cp->sibling;
            delete oldCp;
        }
    }

    delete minNodeHead;

    Cell * newHead = binomialHeapUnion(head, head_);
    head = newHead;

    count--;
    return minKey;
}
void ExtraPriorityQueue::binomialLink(Cell * & binomialTreeY, Cell * & binomialTreeZ) {
    binomialTreeY->parent = binomialTreeZ;
    binomialTreeY->sibling = binomialTreeZ->child;
    binomialTreeZ->child = binomialTreeY;
    (*binomialTreeZ).degree++;
}

Cell * ExtraPriorityQueue::binomialHeapMerge(Cell * & bHx, Cell * & bHy) {
    if (bHx == NULL && bHy == NULL) return NULL;
    else if (bHx != NULL && bHy == NULL) return bHx;
    else if (bHx == NULL && bHy != NULL) return bHy;
    else {
        Cell * cpx = bHx;
        Cell * cpy = bHy;
        Cell * cpMerged = NULL;

        Cell * bHMerged = new Cell;
        bHMerged->sibling = NULL;
        cpx = cpx->sibling;

        // create the appropriate number of cells
        while (cpx != NULL) {
            Cell * cpm = new Cell;
            cpm->parent = NULL;
            cpm->sibling = bHMerged;
            bHMerged = cpm;
            cpx = cpx->sibling;
        }

        while (cpy != NULL) {
            Cell * cpm = new Cell;
            cpm->parent = NULL;
            cpm->sibling = bHMerged;
            bHMerged = cpm;
            cpy = cpy->sibling;
        }

        cpx = bHx;
        cpy = bHy;
        cpMerged = bHMerged;

        // Main merge routine
        while (cpx != NULL && cpy != NULL) {
            if (cpx->degree <= cpy->degree) {
                cpMerged->degree = cpx->degree;
                cpMerged->child = cpx->child;
                cpMerged->key = cpx->key;
                cpx = cpx->sibling;
            } else {
                cpMerged->degree = cpy->degree;
                cpMerged->child = cpy->child;
                cpMerged->key = cpy->key;
                cpy = cpy->sibling;
            }
            cpMerged = cpMerged->sibling;
        }

        if (cpx == NULL) {
            while (cpy != NULL) {
                cpMerged->degree = cpy->degree;
                cpMerged->child = cpy->child;
                cpMerged->key = cpy->key;
                cpy = cpy->sibling;
                cpMerged = cpMerged->sibling;
            }
        }

        if (cpy == NULL) {
            while (cpx != NULL) {
                cpMerged->degree = cpx->degree;
                cpMerged->child = cpx->child;
                cpMerged->key = cpx->key;
                cpx = cpx->sibling;
                cpMerged = cpMerged->sibling;
            }
        }

        // Cleaning up the old root nodes
        cpx = bHx;
        cpy = bHy;

        while (cpx != NULL) {
            Cell * oldCp = cpx;
            cpx = cpx->sibling;
            delete oldCp;
        }

        while (cpy != NULL) {
            Cell * oldCp = cpy;
            cpy = cpy->sibling;
            delete oldCp;
        }

        return bHMerged;
    }
}

Cell * ExtraPriorityQueue::binomialHeapUnion(Cell * & bHx, Cell * & bHy) {
    Cell * headM = binomialHeapMerge(bHx, bHy);
    if (headM == NULL) return NULL;

    Cell * prevX = NULL;
    Cell * x = headM;
    Cell * nextX = x->sibling;

    while (nextX != NULL) {
        if ((x->degree != nextX->degree) ||
            (nextX->sibling != NULL && nextX->sibling->degree == x->degree)) {
            prevX = x;
            x = nextX;
        } else if (x->key <= nextX->key) {
            x->sibling = nextX->sibling;
            binomialLink(nextX, x);
        } else if (prevX == NULL) {
            headM = nextX;
            binomialLink(x, nextX);
            x = nextX;
        } else {
            prevX->sibling = nextX;
            binomialLink(x, nextX);
            x = nextX;
        }
        nextX = x->sibling;
    }

    return headM;
}
