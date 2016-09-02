/******************************************************************************
 * File: UnionFind.cpp
 *
 * Implementation of the UnionFind interface. Doesn't do bounds checking for
 * any operations. Client's responsibility to do bounds checking.
 */

#include "UnionFind.h"

UnionFind::UnionFind(int n) {
    id = new int[n];
    sz = new int[n];
    count = n;

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
        id[p] = id[id[p]];
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
    int i = find(p);
    int j = find(q);
    if (i == j) return;
    if (sz[i] < sz[j]) {
        id[i] = j;
        sz[i] += sz[j];
    } else {
        id[j] = i;
        sz[i] += sz[j];
    }
    count--;
}
