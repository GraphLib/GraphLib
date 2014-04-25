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
#include "adjlist.hpp"
#include "edgelist.hpp"
#include "edge.hpp"
#include "dijkstra.hpp"

class AdjMatrix
{
    // Adjacency matrix
    std::vector< std::vector < int > > G;
public:
    typedef std::vector< int >::iterator iterator;
    // Number of vertices
    int maxVertexNum;
    // Infinity
    int infinity;
    // 
    AdjMatrix() { maxVertexNum = -1; infinity = INT_MAX - 1; }
    AdjMatrix(int inf) { maxVertexNum = -1; infinity = inf; }
    AdjMatrix(std::vector< std::vector< int > > g, int inf);
    AdjMatrix(unsigned size, int inf);
    ~AdjMatrix()
    {
        for (int i = 0; i < G.size(); ++i)
            G[i].clear();
        G.clear();
    }

    void resize(unsigned size)
    {
        G.resize(size);
        for (int i = 0; i < size; ++i)
            G[i].resize(size);
        maxVertexNum = size - 1; 
    }
    void addEdge(Edge edge);
    void addVertex();
    void deleteEdge(unsigned FirstVertexNum, unsigned SecondVertexNum);
    
    EdgeList toEdgeList();
    
    iterator begin(unsigned u) { return (u >= G.size()) ? G[0].begin() : G[u].begin(); }
    iterator end(unsigned u) { return (u >= G.size()) ? G[0].begin() : G[u].end(); }
    
    friend std::istream& operator>> (std::istream& in, AdjMatrix& matr);
    friend std::ostream& operator<< (std::ostream& out, AdjMatrix& matr);

    // Parallel Floyd Algorithm
    void ParallelFloyd(std::vector< std::vector< int > >& PathMatrix);
};

AdjMatrix::AdjMatrix(std::vector< std::vector< int > > g, int inf)
{
    G = g;
    maxVertexNum = G.size() - 1;
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

void AdjMatrix::addEdge(Edge edge)
{
    G[edge.u][edge.v] = edge.weight;   
}

void AdjMatrix::addVertex()
{
    std::vector<int> forNew;
    forNew.resize(maxVertexNum + 1);
    for (int j = 0; j < maxVertexNum; ++j)
        forNew[j] = infinity;
    forNew[maxVertexNum] = 0;
    G.push_back(forNew);
}

void AdjMatrix::deleteEdge(unsigned FirstVertexNum, unsigned SecondVertexNum)
{
    if (FirstVertexNum > maxVertexNum || SecondVertexNum > maxVertexNum || FirstVertexNum == SecondVertexNum)
        throw "This edge not exists!";
    else
        G[FirstVertexNum][SecondVertexNum] = infinity;
}

EdgeList AdjMatrix::toEdgeList()
{
    EdgeList g;
    g.infinity = infinity;
    //g.maxVertexNum = maxVertexNum;
    Edge newEdge;
    for (unsigned i = 0; i < G.size(); ++i)
        for (unsigned j = 0; j < G[i].size(); ++j)
        {
            if (G[i][j] != infinity && i != j)
            {
                newEdge.u = i;
                newEdge.v = j;
                newEdge.weight = G[i][j];
                g.addEdge(newEdge);
            }
        }
    return g;    
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


