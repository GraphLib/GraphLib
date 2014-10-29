/* 
 * File:   all_shortest_paths.hpp
 * Author: alex, svyat
 *
 * Created on April 5, 2014, 12:20 PM
 */

#ifndef ALL_SHORTEST_PATHS_HPP
#define	ALL_SHORTEST_PATHS_HPP

#include <assert.h>
#include <omp.h>
#include "graph.hpp"
#include "shortest_paths.hpp"

int min_of_weights(int a, int b, int infinity)
{
    if (a == infinity) return b;
    else
    {
        if (b != infinity) return std::min(a, b);
        else return a;
    }
}

/**
 * ParallelFloyd() - finds all shortest paths in graph (using Floyd's algorithm)
 * @param g - graph
 * @param distance - matrix for shortest distances between vertices
 */
void ParallelFloyd(Graph& g, std::vector< std::vector< int > >& distance)
{
    int t1, t2;
    g.toAdjMatrix();
    distance.resize(g.verticesCount());
    for (int i = 0, n = g.verticesCount(); i < n; ++i)
        distance[i].assign(g.adjMatrix[i].begin(), g.adjMatrix[i].end());
    omp_set_num_threads(8);
    for (int k = 0; k < distance.size(); ++k)
    #pragma omp parallel for private (t1, t2)
      for (int i = 0; i < distance.size(); ++i)
        if (distance[i][k] != g.infinity)
          for (int j = 0; j < distance.size(); ++j)
            if (distance[k][j] != g.infinity)
                distance[i][j] = min_of_weights(distance[i][j],
                        distance[i][k] + distance[k][j], g.infinity);
}

/**
 * ParallelJohnson() - finds all shortest paths in graph (Johnson's algorithm)
 * @param g - graph
 * @param distance - matrix for shortest distances between vertices
 * @param predecessor - matrix for shortest paths (predecessors)
 * @return false, if negative cycle was detected, and true - otherwise
 */
bool ParallelJohnson(Graph &g, std::vector< std::vector< int > >& distance,
        std::vector< std::vector<int> >& predecessor)
{
    g.resize(g.verticesCount() + 1);
    for (unsigned i = 0, n = (unsigned)g.verticesCount() - 1; i < n; ++i)
        g.addEdge(Edge(n, i, 0));
    std::vector<int> h;
    if (BellmanFord(g, h, g.verticesCount() - 1))
        return false;
    for (int i = 0; i < g.edgeList.size(); ++i)
        g.edgeList[i].weight += h[g.edgeList[i].u] - h[g.edgeList[i].v];
    omp_set_num_threads(8);
    distance.resize(g.verticesCount() - 1);
    predecessor.resize(g.verticesCount() - 1);
    g.toAdjList();
    unsigned n = (unsigned)g.verticesCount() - 1;
    for (unsigned i = 0; i < n; ++i)
        g.deleteEdge(n, i);
    g.resize(g.verticesCount() - 1);
    #pragma omp parallel for
    for (int i = 0; i < n; ++i)
    {
        Dijkstra(g, distance[i], predecessor[i], i);
        for (unsigned j = 0; j < n; ++j)
            if (distance[i][j] != g.infinity)
                distance[i][j] += h[j] - h[i];
    }
    for (unsigned i = 0; i < n; ++i)
        for (int j = 0; j < g.adjList[i].size(); ++j)
            g.adjList[i][j].first -= h[i] - h[g.adjList[i][j].second];
    return true;
}
#endif	/* ALL_SHORTEST_PATHS_HPP */
