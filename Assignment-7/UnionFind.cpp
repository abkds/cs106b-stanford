/******************************************************************************
 * File: UnionFind.cpp
 *
 * Implementation of the UnionFind interface. Doesn't do bounds checking for
 * any operations. Client's responsibility to do bounds checking.
 */

#include "UnionFind.h"

UnionFind::UnionFind(int n) {
    int *id = new int[n];
    int *sz = new int[n];
    int count = n;

    /* Each node is it's own component. The size of each component is 1 */
    for (int i = 0; i < n; i++) {
        id[i] = i;
        sz[i] = 1;
    }
}

UnionFind::~UnionFind() {
    /* Free dynamically allocated array */
    delete id;
    delete sz;
}

/* Implementation notes
 * --------------------
 * Loop until the node is parent of itself.
 */
int UnionFind::find(int p) const {
    while (p != id[p]) {
        p = id[p];
    }
    return p;
}

/* Nothing magical here. Simply returning the count */
int UnionFind::components() const {
    return count;
}

/* If both in same component return true */
bool UnionFind::connected(int p, int q) const {
    if (find(p) == find(q)) return true;
    return false;
}

/* Implementation notes
 * --------------------
 * If already connected do nothing.
 *
 * To connect to components one component is made the child of the root
 * of another component. To maintain that the trees do not become long in
 * height, always the smaller tree is made a child of the larger tree.
 */
void UnionFind::connect(int p, int q) {
    if (!connected(p, q)) {
        if (sz[p] < sz[q]) {
            id[p] = q;
            sz[q] += sz[p];
        } else {
            id[q] = p;
            sz[p] += sz[q];
        }
        count--;
    }
}
