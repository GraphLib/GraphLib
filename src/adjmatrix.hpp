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
        // ? maxVertexNum = size; 
    }
    void addEdge(Edge edge);
    void addVertex();
    void deleteEdge(unsigned FirstVertexNum, unsigned SecondVertexNum);
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

std::istream& operator>> (std::istream& in, AdjMatrix& matr)
{
    int n, m;
    in >> n >> m;
    matr.resize(n + 1);
    for (int i = 0; i < n + 1; ++i)
        for (int j = 0; j < n + 1; ++j)
        {
            int weight;
            i == j ? weight = 0 : weight = matr.infinity;
            Edge e(i, j, weight);  
            matr.addEdge(e);
        }
    Edge edge;
    for (int i = 0; i < m; ++i)
    {
        in >> edge;
        matr.addEdge(edge);
        /* in case of graph is undirected
        
         */
    }
    return in;
}

std::ostream& operator<< (std::ostream& out, AdjMatrix& matr)
{
    for (int i = 0; i < matr.G.size(); ++i)
        for (int j = 0; j < matr.G[i].size(); ++j)
            if (matr.infinity != matr.G[i][j] && 0 != matr.G[i][j])
                out << i << ' ' << j << ' ' << matr.G[i][j] << '\n';
    return out;
}

#endif	/* ADJMATRIX_HPP */


