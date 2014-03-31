/* 
 * File:   dsu.hpp
 * Author: svyat
 *
 * Description: Disjoint set union data structure
 * Created on March 31, 2014, 1:03 PM
 */

#ifndef DSU_HPP
#define	DSU_HPP

class DSU
{
    inline int root(int x);
    std::vector<int> p, rank;
public:
    bool unite(int a, int b);
    DSU(int n = 0)
    {
        p.resize(n + 1);
        rank.resize(n + 1);
        for (int i = 0; i <= n; ++i)
            p[i] = i;
    }
    ~DSU()
    {
        p.clear();
        rank.clear();
    }
};

inline int DSU::root(int x)
{
    return p[x] == x ? x : p[x] = root(p[x]);
}

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

