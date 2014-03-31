/* 
 * File:   dijkstra.hpp
 * Author: svyat
 *
 * Created on March 31, 2014, 5:05 PM
 */

#ifndef DIJKSTRA_HPP
#define	DIJKSTRA_HPP

#include <set>
#include <assert.h>
#include "adjlist.hpp"

bool nonnegativeEdges(AdjList &g)
{
    int n = g.maxVertexNum;
    for (unsigned i = 0; i <= n; ++i)
        for (AdjList::iterator it = g.begin(i); it != g.end(i); ++it)
            if (it->first < 0)
                return false;
    return true;
}

void Dijkstra(AdjList g, std::vector<int>& distance,
        std::vector<int>& predecessor, unsigned start, int inf)
{
    assert(nonnegativeEdges(g));
    distance.clear();
    predecessor.clear();
    distance.assign(g.maxVertexNum + 1, inf);
    predecessor.assign(g.maxVertexNum + 1, -1);
    distance[start] = 0;
    std::set< std::pair<int, unsigned> > Q;
    Q.insert(std::make_pair(distance[start], start));
    std::pair<int, unsigned> extracted;
    while (!Q.empty())
    {
        extracted = *Q.begin();
        Q.erase(Q.begin());
        unsigned u = extracted.second;
        unsigned v;
        int w;
        for (AdjList::iterator it = g.begin(u); it != g.end(u); ++it)
        {
            v = it->second;
            w = it->first;
            if (distance[v] > distance[u] + w)
            {
                Q.erase(std::make_pair(distance[v], v));
                distance[v] = distance[u] + w;
                Q.insert(std::make_pair(distance[v], v));
                predecessor[v] = u;
            }
        }
    }
}

#endif	/* DIJKSTRA_HPP */

