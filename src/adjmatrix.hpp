/* 
 * File:   adjmatrix.hpp
 * Author: alex, svyat
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
}

AdjMatrix::AdjMatrix(std::vector< std::vector< int > > g, int inf)
{
    G = g;
    maxVertexNum = (int)G.size() - 1;
    infinity = inf;        
}

AdjMatrix::AdjMatrix(unsigned size, int inf)
{
    this->resize(size);
    infinity = inf;
    maxVertexNum = size;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (i == j) G[i][j] = 0;
            else G[i][j] = inf;
}

AdjMatrix::~AdjMatrix()
{
    clear();
}

int AdjMatrix::addEdge(Edge edge)
{
    /*if (G[edge.u][edge.v] != infinity)
        return 1;*/
    G[edge.u][edge.v] = G[edge.v][edge.u] = edge.weight;   
    return 0;
}

int AdjMatrix::deleteEdge(unsigned u, unsigned v)
{
    if (u > maxVertexNum || v > maxVertexNum || u == v)
        return 1;
    else G[u][v] = G[v][u] = infinity;    
}

void AdjMatrix::clear()
{
    for (int i = 0; i < G.size(); ++i)
        G[i].clear();
    G.clear();
    maxVertexNum = -1;
}

void AdjMatrix::toAdjList(AdjList &g)
{
    g.resize(maxVertexNum + 1);
    g.infinity = infinity;
    g.maxVertexNum = maxVertexNum;
    for (int i = 0; i <= maxVertexNum; ++i)
        for (int j = i + 1; j <= maxVertexNum; ++j)
            if (G[i][j] != infinity)
                g.addEdge(Edge(i, j, G[i][j]), false);
}

void AdjMatrix::toEdgeList(EdgeList &g)
{
    g.maxVertexNum = maxVertexNum;
    g.infinity = infinity;
    for (unsigned i = 0; i < G.size(); ++i)
        for (int j = i + 1; j < G[i].size(); ++j)
            if (G[i][j] != infinity)
                g.addEdge(Edge(i, j, G[i][j]));
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
            if (matr.infinity != matr.G[i][j] && 0 != matr.G[i][j])
                out << i << ' ' << j << ' ' << matr.G[i][j] << '\n';
        if (j != matr.G.size())
            throw "Writing error!";        
    }
    if (i != matr.G.size())
        throw "Writing error!";
    return out;
}

#endif	/* ADJMATRIX_HPP */
