/* 
 * File:   adjmatrix.hpp
 * Author: alex
 *
 * Created on April 5, 2014, 11:23 AM
 */

#ifndef ADJMATRIX_HPP
#define	ADJMATRIX_HPP

#include <vector>
#include <assert.h>
#include <limits.h>
#include "edge.hpp"
#include "data_structures.hpp"

AdjMatrix::AdjMatrix()
{
    maxVertexNum = -1;
    infinity = INT_MAX;
    directed = false;
}

/**
 * Constructor
 * @param directed - true, if edges are directed, false - otherwise
 */
AdjMatrix::AdjMatrix(bool directed)
{
    maxVertexNum = -1;
    infinity = INT_MAX;
    this->directed = directed;
}


/**
 * Constructor
 * @param g - adjacency matrix
 * @param infinity - designation of infinity (if edge doesn't exist)
 * @param directed - true, if edges are directed, and false - otherwise
 */
AdjMatrix::AdjMatrix(std::vector< std::vector< int > > g, int inf,
        bool directed) : G(g)
{
    maxVertexNum = (int)G.size() - 1;
    infinity = inf;
    this->directed = directed;
}

/**
 * Constructor
 * @param size - number of vertices
 * @param inf - designation of infinity (if edge doesn't exist)
 * @param directed - true, if edges are directed, and false - otherwise
 */
AdjMatrix::AdjMatrix(unsigned size, int inf, bool directed)
{
    this->resize(size);
    infinity = inf;
    maxVertexNum = size;
    this->directed = directed;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (i == j) G[i][j] = 0;
            else G[i][j] = inf;
}

/**
 * Destructor
 */
AdjMatrix::~AdjMatrix()
{
    clear();
}

/**
 * resize() - changes number of vertices
 * @param size - new number of vertices
 */
void AdjMatrix::resize(unsigned size)
{
    G.resize(size);
    for (int i = 0; i < size; ++i)
        G[i].resize(size);
    maxVertexNum = (int)size - 1; 
}

/**
 * addEdge() - adds edge
 * @param edge - new edge
 * @param checkExistence - true, if it needs to check existence of edge,
 * false - otherwise
 * @return 0, if edge was added, and 1 - otherwise
 */
int AdjMatrix::addEdge(Edge edge, bool checkExistence)
{
    if (checkExistence)
    {
        if (G[edge.u][edge.v] != infinity)
            return 1;
    }
    G[edge.u][edge.v] = edge.weight;
    if (!directed)
        G[edge.v][edge.u] = edge.weight;
    return 0;
}

/**
 * deleteEdge() - removes the edge
 * @param u - first vertex of edge
 * @param v - second vertex of edge
 * @return 0, if edge was deleted, and 1 - otherwise
 */
int AdjMatrix::deleteEdge(unsigned u, unsigned v)
{
    if (u > maxVertexNum || v > maxVertexNum || u == v)
        return 1;
    else
    {
        G[u][v] = infinity;
        if (!directed)
            G[v][u] = infinity;
    }
    return 0;
}

/**
 * addVertex() - adds vertex
 */
void AdjMatrix::addVertex()
{
    std::vector<int> forNew;
    forNew.resize(maxVertexNum + 1);
    for (int j = 0; j < maxVertexNum; ++j)
        forNew[j] = infinity;
    forNew[maxVertexNum] = 0;
    G.push_back(forNew);
}

/**
 * clear() - clears graph
 */
void AdjMatrix::clear()
{
    for (int i = 0; i < G.size(); ++i)
        G[i].clear();
    G.clear();
    maxVertexNum = -1;
}

/**
 * toAdjList() - convert graph (adjacency matrix) to adjacency list
 * @param g - adjacency list for this graph 
 */
void AdjMatrix::toAdjList(AdjList &g)
{
    g.resize(maxVertexNum + 1);
    g.infinity = infinity;
    g.maxVertexNum = maxVertexNum;
    g.directed = directed;
    for (unsigned i = 0; i <= maxVertexNum; ++i)
        for (unsigned j = 0; j <= maxVertexNum; ++j)
            if (G[i][j] != infinity && i != j)
                g.addEdge(Edge(i, j, G[i][j]), false);
}

/**
 * toEdgeList() - converts graph (adjacency matrix) to edge list
 * @param g - edge list for this graph
 */
void AdjMatrix::toEdgeList(EdgeList &g)
{
    g.maxVertexNum = maxVertexNum;
    g.infinity = infinity;
    g.directed = directed;
    for (unsigned i = 0; i < G.size(); ++i)
        for (unsigned j = 0; j < G[i].size(); ++j)
            if (G[i][j] != infinity && i != j)
                g.addEdge(Edge(i, j, G[i][j]), false);
}

std::vector<int> &AdjMatrix::operator [](int i)
{
    return G[i];
}

std::istream& operator>> (std::istream& in, AdjMatrix& matr)
{
    int n, m, i;
    in >> n >> m;
    matr.resize(n);
    int weight;
    for (i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
            i == j ? weight = 0 : weight = matr.infinity;
            matr.G[i][j] = weight;
        }
    unsigned u, v;
    for (i = 0; i < m; ++i)
    {
        in >> u >> v >> weight;
        matr.G[u][v] = weight;
    }
    if (i != m)
        throw "Reading error!";
    return in;
}

std::ostream& operator<< (std::ostream& out, AdjMatrix& matr)
{
    int i, j;
    for (i = 0; i < matr.G.size(); ++i)
    {
        for (j = 0; j < matr.G[i].size(); ++j)
            if (matr.infinity != matr.G[i][j] && i != j)
                out << i << ' ' << j << ' ' << matr.G[i][j] << '\n';
        if (j != matr.G.size())
            throw "Writing error!";        
    }
    if (i != matr.G.size())
        throw "Writing error!";
    return out;
}

#endif	/* ADJMATRIX_HPP */
