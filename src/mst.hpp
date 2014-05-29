/* 
 * File:   mst.hpp
 * Author: svyat
 *
 * Created on March 31, 2014, 12:56 PM
 */

#ifndef MST_HPP
#define	MST_HPP

#include <algorithm>
#include "graph.hpp"
#include "dsu.hpp"
#include <omp.h>

/**
 * merge() - merges two sorted subarrays into the one
 * @param eList - list of edges
 * @param l - left bound of the first subarray
 * @param m - right bound of the first subarray
 * @param r - right bound of the second subarray
 */
void merge(EdgeList &eList, int l, int m, int r)
{
    std::vector<Edge> tmp;
    int pos1 = l;
    int pos2 = m;
    while (pos1 < m && pos2 < r)
    {
        if (eList[pos1] < eList[pos2])
            tmp.push_back(eList[pos1++]);
        else tmp.push_back(eList[pos2++]);
    }
    while (pos1 < m)
        tmp.push_back(eList[pos1++]);
    while (pos2 < r)
        tmp.push_back(eList[pos2++]);
    for (int i = 0; i < r - l; ++i)
        eList[l + i] = tmp[i];
    tmp.clear();
}

/**
 * ParellelSort() - sorts list of edges by weight in non-descending order
 * @param eList - list of edges
 */
void ParallelSort(EdgeList &eList)
{
    int threads = omp_get_max_threads();
    omp_set_num_threads(threads);
    std::vector<int> index(threads + 1);
    int size = eList.size() / threads;
    for (int i = 0; i < threads; ++i)
        index[i] = i * size;
    index[threads] = eList.size();
#pragma omp parallel for private(i)
    for (int i = 0; i < threads; ++i)
        std::sort(eList.begin() + index[i], eList.begin() + index[i + 1]);
    while (index.size() != 2)
    {
#pragma omp parallel for private(i)
        for (int i = 0; i < (int)index.size() - 2; i += 2)
            merge(eList, index[i], index[i + 1], index[i + 2]);
        for (int i = (int)index.size() - 1; i >= 0; --i)
            if (i & 1)
                index.erase(index.begin() + i);
    }
}

/**
 * ParallelKruskal() - finds minimal spanning tree in undirected graph
 * @param g - graph
 * @param mst - edge list of minimal spanning tree
 * @return 1, if graph is directed, and 0 - otherwise
 */
int ParallelKruskal(Graph g, std::vector<Edge>& mst)
{
    if (g.directed)
        return 1;
    g.toEdgeList();
    DSU dsu(g.verticesCount());
    g.edgeList.sort();
    for (int i = 0; i < g.edgeList.size(); ++i)
        if (dsu.unite(g.edgeList[i].u, g.edgeList[i].v))
            mst.push_back(g.edgeList[i]);
    return 0;
}

#endif	/* MST_HPP */
