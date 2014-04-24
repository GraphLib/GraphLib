/* 
 * File:   all_shortest_paths.hpp
 * Author: alex
 *
 * Created on April 5, 2014, 12:20 PM
 */

#ifndef ALL_SHORTEST_PATHS_HPP
#define	ALL_SHORTEST_PATHS_HPP

#include <assert.h>
#include "adjmatrix.hpp"

int Min(int A, int B, int inf)
{
  int Result = (A < B) ? A : B;

  if((A == inf) && (B != inf)) Result = B;
  if((B == inf) && (A != inf)) Result = A;
  if((A == inf) && (B == inf)) Result = inf;

  return Result;
}

void AdjMatrix::ParallelFloyd(std::vector< std::vector< int > >& PathMatrix)
{
    PathMatrix.assign(G.begin(), G.end());
    int t1, t2;
    //omp_set_num_threads(omp_get_num_threads())
    //omp_set_num_threads(8);
    for (int k = 0; k < PathMatrix.size(); ++k)
  //#pragma omp parallel for private (t1, t2)
      for (int i = 0; i < PathMatrix.size(); ++i)
        if (PathMatrix[i][k] != infinity)
          for (int j = 0; j < PathMatrix.size(); ++j)
            if (PathMatrix[k][j] != infinity) 
            {
                t1 = PathMatrix[i][j];
                t2 = PathMatrix[i][k] + PathMatrix[k][j];
                PathMatrix[i][j] = Min(t1, t2, infinity);
            }
}

void AdjList::ParallelJohnson(std::vector< std::vector< int > >& PathMatrix)
{
    PathMatrix.resize(G.size());
    // Delete this?
    /*for (int i = 0; i < PathMatrix.size(); ++i)
        PathMatrix[i].resize(G.size());
    for (int i = 0; i < PathMatrix.size(); ++i)
        for (int j = 0; j < PathMatrix[i].size(); ++j)
            i == j ? PathMatrix[i][j] = infinity : PathMatrix[i][j] = 0;*/
    this->addVertex();
    Edge e;
    for (int i = 0; i < G.size() - 1; ++i)
    {
        e.u = maxVertexNum;
        e.v = i;
        e.weight = 0;
        this->addEdgeForJohnson(e);
    }
    std::vector<int> h;
    std::vector<int> paths;
    //this->BellmanFord(maxVertexNum, h, paths)
    /*for (int i = 0; i < G.size() - 1; ++i)
        for (int j = 0; j < G[i].size(); ++j)
            G[i][j].first = G[i][j].first + h[i] - h[j];*/
    //omp_set_num_threads(omp_get_num_threads())
  //#pragma omp parallel for
    for (int i = 0; i < G.size() - 1; ++i)
        this->Dijkstra(i, PathMatrix[i], paths);
    /*for (int i = 0; i < G.size() - 1; ++i)
        for (int j = 0; j < G[i].size(); ++j)
        {
            G[i][j].first = G[i][j].first - h[i] + h[j];
            PathMatrix[i][j] = PathMatrix[i][j] - h[i] + h[j];
        }*/
    G.pop_back();
}

#endif	/* ALL_SHORTEST_PATHS_HPP */
