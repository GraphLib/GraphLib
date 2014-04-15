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
        for (int j = 0; j < PathMatrix.size(); ++j)
          if ((PathMatrix[i][k] != infinity) && (PathMatrix[k][j] != infinity)) 
          {
              t1 = PathMatrix[i][j];
              t2 = PathMatrix[i][k] + PathMatrix[k][j];
              PathMatrix[i][j] = Min(t1, t2, infinity);
          }
}

#endif	/* ALL_SHORTEST_PATHS_HPP */
