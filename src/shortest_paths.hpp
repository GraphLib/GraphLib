/* 
 * File:   shortest_paths.hpp
 * Author: alex, svyat
 *
 * Created on April 6, 2014, 3:23 PM
 */

#ifndef SHORTEST_PATHS_HPP
#define	SHORTEST_PATHS_HPP

#include <set>
#include <assert.h>
#include "graph.hpp"

/**
 * nonnegativeEdges - detects presence of negative edges
 * @param g - graph
 * @return true, if there are no negative edges, false - otherwise
 */
bool nonnegativeEdges(Graph &g)
{
    int n = g.verticesCount();
    for (unsigned i = 0; i < n; ++i)
        for (int j = 0; j < g.adjList[i].size(); ++j)
            if (g.adjList[i][j].first < 0)
                return false;
    return true;
}

/**
 * BellmanFord() - find shortest paths from 1 vertex to all in graph
 * @param g - graph
 * @param distance - array for shortest distances
 * @param start - start vertex
 * @return true, if negative cycle found, and false - otherwise
 */
bool BellmanFord(Graph &g, std::vector<int>& distance, unsigned start)
{
    if (!g.directed)
        return false;
    distance.clear();
    distance.assign(g.verticesCount(), g.infinity);
    std::vector<int> D(g.verticesCount());
    distance[start] = 0;
    g.toEdgeList();
    for (int i = 0, n = g.verticesCount(); i < n; ++i)
    {
        for (int j = 0; j < g.edgeList.size(); ++j)
        {
            if (D[g.edgeList[j].v] > D[g.edgeList[j].u] + g.edgeList[j].weight)
            {
                D[g.edgeList[j].v] = D[g.edgeList[j].u] + g.edgeList[j].weight;
                if (i == n - 1)
                    return true;
            }
            if (distance[g.edgeList[j].u] != g.infinity &&
                    distance[g.edgeList[j].v] > distance[g.edgeList[j].u] +
                    g.edgeList[j].weight)
                distance[g.edgeList[j].v] = distance[g.edgeList[j].u] +
                        g.edgeList[j].weight;
        }
    }
    distance.pop_back();
    D.clear();
    return false;
}

/**
 * Dijkstra() - find shortest paths from one vertex to all in graph
 * @param g - graph
 * @param distance - array for shortest distances
 * @param predecessor - array for shortest paths (predecessors)
 * @param start - start vertex
 * @return 1, if start vertex is incorrect, 2 - if there's negative edge
 * and 0 - otherwise
 */
int Dijkstra(Graph &g, std::vector<int>& distance,
        std::vector<int>& predecessor, unsigned start)
{
    g.toAdjList();
    if ((int)start >= g.verticesCount())
        return 1;
    if (!nonnegativeEdges(g))
        return 2;
    distance.clear();
    predecessor.clear();
    distance.assign(g.verticesCount(), g.infinity);
    predecessor.assign(g.verticesCount(), -1);
    distance[start] = 0;
    std::set<std::pair<int, unsigned> > Q;
    Q.insert(std::make_pair(distance[start], start));
    std::pair<int, unsigned> extracted;
    while (!Q.empty())
    {
        extracted = *Q.begin();
        Q.erase(Q.begin());
        unsigned u = extracted.second;
        unsigned v;
        int w;
        for (int i = 0; i < g.adjList[u].size(); ++i)
        {
            v = g.adjList[u][i].second;
            w = g.adjList[u][i].first;
            if ((distance[v] > distance[u] + w) || distance[v] == g.infinity))
            {
                Q.erase(std::make_pair(distance[v], v));
                distance[v] = distance[u] + w;
                Q.insert(std::make_pair(distance[v], v));
                predecessor[v] = u;
            }
        }
    }
    return 0;
}

#endif /* SHORTEST_PATHS_HPP */
