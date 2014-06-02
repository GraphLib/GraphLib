/* 
 * File:   dsu.hpp
 * Author: svyat
 *
 * Description: Disjoint set union data structure
 * Created on March 31, 2014, 1:03 PM
 */

#ifndef DSU_HPP
#define	DSU_HPP

/**
 * DSU - implementation of data structure disjoint-set union
 */
class DSU
{
    inline int root(int);
    std::vector<int> p, rank;
public:
    bool unite(int, int);
    DSU(int);
    ~DSU();
};

/**
 * Constructor
 * @param n - initial number of sets
 */
DSU::DSU(int n)
{
    p.resize(n + 1);
    rank.resize(n + 1);
    for (int i = 0; i <= n; ++i)
        p[i] = i;
}

/**
 * Destructor
 */
DSU::~DSU()
{
    p.clear();
    rank.clear();
}

/**
 * root() - finds leader of parent set by some element
 * @param x - some element
 * @return leader of set
 */
inline int DSU::root(int x)
{
    return p[x] == x ? x : p[x] = root(p[x]);
}

/**
 * unite() - merges two parent sets by some two elements
 * @param a - first element
 * @param b - second element
 * @return true, if both of elements from the same set, and false - otherwise
 */
bool DSU::unite(int a, int b)
{
    a = root(a);
    b = root(b);
    if (a == b)
        return false;
    if (rank[a] > rank[b])
        std::swap(a, b);
    p[a] = b;
    if (rank[a] == rank[b])
        ++rank[a];
    return true;
}
#endif	/* DSU_HPP */
