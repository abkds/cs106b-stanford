/******************************************************************************
 * File: UnionFind.h
 *
 * Interface for union find data structure. A slick data structure which
 * provides connectivity between two points and union between two clusters
 * in logarithmic time.
 */

#ifndef UnionFind_Included
#define UnionFind_Included

class UnionFind {
public:
    /* Explicit constructor, initialize union find with n points */
    UnionFind(int n);
    ~UnionFind();

    /* Function: connected
     * Usage: if (connected(p, q)) { ... }
     * -------------------------------
     * Returns whether the node represented by p and q are connected.
     */
    bool connected(int p, int q) const;

    /* Function: union
     * Usage: union(p, q)
     * ------------------
     * Merges the component containing p and the component containing q
     */
    void connect(int p, int q);

    /* Function: count
     * Usage: n = count();
     * -------------------
     * Returns the number of components.
     */
    int components() const;

    /* Function: find
     * Usage: n = find(p)
     * ------------------
     * Returns the component identifier for given node
     */
    int find(int p) const;
private:
    /* Internally it uses two dynamically allocated arrays, one to maintain
     * the parent node of a given node and another to maintain the size of
     * the given component. Size array helps in determining, which root to
     * make the new root when doing union operation on two components.
     */
    int *sz;
    int *id;

    /* Number of components */
    int count;
};

#endif
