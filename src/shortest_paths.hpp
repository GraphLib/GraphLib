/* 
 * File:   shortest_paths.hpp
 * Author: alex, svyat
 *
 * Created on April 6, 2014, 3:23 PM
 */

#ifndef SHORTEST_PATHS_HPP
#define	SHORTEST_PATHS_HPP

#include <vector>
#include <assert.h>
#include "adjlist.hpp"
#include "adjmatrix.hpp"
#include "edgelist.hpp"
#include "edge.hpp"
#include <set>

bool AdjList::nonnegativeEdges()
{
    for (unsigned i = 0; i < G.size(); ++i)
        for (unsigned j = 0; j < G[i].size(); ++j)
            if (G[i][j].first < 0)
                return false;
    return true;
}

void AdjList::Dijkstra(unsigned start, std::vector<int>& distance, std::vector<int>& predecessor)
{
    assert(nonnegativeEdges());
    distance.clear();
    predecessor.clear();
    distance.assign(maxVertexNum, infinity);
    predecessor.assign(maxVertexNum, -1);
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
        for (int i = 0; i < G[u].size(); ++i)
        {
            v = G[u][i].second;
            w = G[u][i].first;
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

#endif
