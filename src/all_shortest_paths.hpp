/* 
 * File:   all_shortest_paths.hpp
 * Author: alex, svyat
 *
 * Created on April 5, 2014, 12:20 PM
 */

#ifndef ALL_SHORTEST_PATHS_HPP
#define	ALL_SHORTEST_PATHS_HPP

#include <assert.h>
#include "graph.hpp"
#include "shortest_paths.hpp"

void ParallelFloyd(Graph& g, std::vector< std::vector< int > >& d)
{
    g.toAdjMatrix();
    d.resize(g.verticesCount());
    for (int i = 0, n = g.verticesCount(); i < n; ++i)
        d[i].assign(g.adjMatrix[i].begin(), g.adjMatrix[i].end());
    //omp_set_num_threads(omp_get_num_threads())
    //omp_set_num_threads(8);
    for (int k = 0; k < d.size(); ++k)
    //#pragma omp parallel for private (t1, t2)
      for (int i = 0; i < d.size(); ++i)
        if (d[i][k] != g.infinity)
          for (int j = 0; j < d.size(); ++j)
            if (d[k][j] != g.infinity)
                d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
}

bool ParallelJohnson(Graph &g, std::vector< std::vector< int > >& distance,
        std::vector< std::vector<int> >& predecessor)
{
    g.resize(g.verticesCount() + 1);
    for (unsigned i = 0, n = (unsigned)g.verticesCount() - 1; i < n; ++i)
        g.addEdge(Edge(i, n, 0));
    std::vector<int> h;
    if (BellmanFord(g, h, g.verticesCount() - 1))
        return false;
    for (int i = 0; i < g.edgeList.size(); ++i)
        g.edgeList[i].weight += h[g.edgeList[i].u] - h[g.edgeList[i].v];
    //omp_set_num_threads(omp_get_num_threads())
    //#pragma omp parallel for
    distance.resize(g.verticesCount() - 1);
    predecessor.resize(g.verticesCount() - 1);
    g.toAdjList();
    for (unsigned i = 0, n = (unsigned)g.verticesCount() - 1; i < n; ++i)
        g.deleteEdge(i, n);
    g.resize(g.verticesCount() - 1);
    for (unsigned i = 0, n = (unsigned)g.verticesCount(); i < n; ++i)
        Dijkstra(g, distance[i], predecessor[i], i);
    for (unsigned i = 0, n = (unsigned)g.verticesCount(); i < n; ++i)
        for (int j = 0; j < g.adjList[i].size(); ++j)
            g.adjList[i][j].first += h[i] - h[g.adjList[i][j].second];
    for (int i = 0; i < g.edgeList.size(); ++i)
        g.edgeList[i].weight += h[g.edgeList[i].v] - h[g.edgeList[i].u];
    return true;
}

#endif	/* ALL_SHORTEST_PATHS_HPP */
