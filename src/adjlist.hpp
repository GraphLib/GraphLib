/* 
 * File:   adjlist.hpp
 * Author: svyat, alex
 *
 * Created on March 31, 2014, 2:02 AM
 */

#ifndef ADJLIST_HPP
#define	ADJLIST_HPP

#include <vector>
#include <limits.h>
#include "edge.hpp"
#include "data_structures.hpp"

AdjList::AdjList()
{
    maxVertexNum = -1;
    infinity = INT_MAX;
    directed = false;
}

/**
 * Constructor
 * @param directed - true, if edges are directed
 */
AdjList::AdjList(bool directed)
{
    maxVertexNum = -1;
    infinity = INT_MAX;
    this->directed = directed;
}

/**
 * Constructor
 * @param size - number of vertices
 * @param infinity - designation of infinity (if edge doesn't exists)
 * @param directed - true, if edges are directed
 */
AdjList::AdjList(unsigned size, int infinity, bool directed)
{
    this->maxVertexNum = (int)size - 1;
    G.resize(size);
    this->infinity = infinity;
    this->directed = directed;
}

/**
 * Constructor
 * @param g - adjacency list
 * @param directed - true, if edges are directed
 */
AdjList::AdjList(std::vector< std::vector<std::pair<int, unsigned> > > g, bool directed)
{
    G = g;
    this->directed = directed;
    infinity = INT_MAX;
    maxVertexNum = -1;
    for (unsigned i = 0; i < g.size(); ++i)
        for (int j = 0; j < g[i].size(); ++j)
            if (maxVertexNum < std::max(g[i][j].second, i))
                maxVertexNum = std::max(g[i][j].second, i);               
}

AdjList::~AdjList()
{
    clear();
}

/**
 * resize() - change number of vertices
 * @param size - new number of vertices
 */
void AdjList::resize(unsigned size)
{
    G.resize(size);
    maxVertexNum = size - 1;
}

/**
 * addVertex() - add vertex
 */
void AdjList::addVertex()
{
    maxVertexNum++;
    std::vector<std::pair<int, unsigned> > forNew;
    forNew.clear();
    G.push_back(forNew);
}

/**
 * addEdge() - add edge
 * @param edge - new edge
 * @param checkExistence - true for checkig existence of edge
 */
int AdjList::addEdge(Edge edge, bool checkExistence)
{
    if (checkExistence)
    {
        if ((int)std::max(edge.u, edge.v) <= maxVertexNum)
        {
            for (int i = 0; i < G[edge.u].size(); ++i)
                if (G[edge.u][i].second == edge.v)
                    return 1;
        }
    }
    if ((int)std::max(edge.u, edge.v) > maxVertexNum)
    {
        maxVertexNum = (int)std::max(edge.u, edge.v);
        resize(maxVertexNum + 1);
    }
    G[edge.u].push_back(std::make_pair(edge.weight, edge.v));
    if (!directed)
        G[edge.v].push_back(std::make_pair(edge.weight, edge.u));
    return 0;
}

/**
 * deleteEdge() - delete edge
 * @param u - first vertex
 * @param v - second vertex
 */
int AdjList::deleteEdge(unsigned u, unsigned v)
{
    // Need to recalc maxvertexnum!!!
    if (u > maxVertexNum || v > maxVertexNum || u == v)
        return 1;
    for (int j = 0; j < G[u].size(); ++j)
    {
        if (G[u][j].second == v)
        {
            for (int k = j; k + 1 < G[u].size(); ++k)
                G[u][k] = G[u][k + 1];
            G[u].pop_back();
            if (directed)
            {
                for (int k = 0; k < G[v].size(); ++k)
                {
                    if (G[v][k].second == u)
                    {
                        for (int i = k; i + 1 < G[v].size(); ++i)
                            G[v][i] = G[v][i + 1];
                        G[v].pop_back();
                        return 0;
                    }
                }
            }
            return 1;
        }
    }
    return 1;
}

/**
 * clear() - clear graph
 */
void AdjList::clear()
{
    for (int i = 0; i < G.size(); ++i)
        G[i].clear();
    G.clear();
    maxVertexNum = -1;
}

/**
 * toAdjMatrix() - convert graph (adjacency list) to adjacency matrix
 * @param g - adjacency matrix for this graph 
 */
void AdjList::toAdjMatrix(AdjMatrix &g)
{
    g.resize(maxVertexNum + 1);
    g.maxVertexNum = maxVertexNum;
    g.infinity = infinity;
    g.directed = directed;
    for (int i = 0; i <= maxVertexNum; ++i)
    {
        for (int j = i + 1; j <= maxVertexNum; ++j)
        {
            g.addEdge(Edge(i, j, infinity));
            if (directed)
                g.addEdge(Edge(j, i, infinity));
        }
    }
    for (unsigned i = 0; i < G.size(); ++i)
        for (int j = 0; j < G[i].size(); ++j)
            g.addEdge(Edge(i, G[i][j].second, G[i][j].first));
}

/**
 * toEdgeList() - convert graph (adjacency list) to edge list
 * @param g - edge list for this graph 
 */
void AdjList::toEdgeList(EdgeList &g)
{
    g.maxVertexNum = maxVertexNum;
    g.infinity = infinity;
    g.directed = directed;
    for (unsigned i = 0; i < G.size(); ++i)
    {
        for (int j = 0; j < G[i].size(); ++j)
        {
            if (!directed && i < G[i][j].second)
                g.addEdge(Edge(i, G[i][j].second, G[i][j].first), false);
            else if (directed)
                g.addEdge(Edge(i, G[i][j].second, G[i][j].first), false);
        }
    }
}

std::vector< std::pair<int, unsigned> >& AdjList::operator [](int i)
{
    return G[i];
}

std::istream& operator>> (std::istream& in, AdjList &list)
{
    int n, m;
    in >> n >> m;
    list.resize(n + 1);
    Edge edge;
    for (int i = 0; i < m; ++i)
    {
        in >> edge;
        list.addEdge(edge, false);
    }
    return in;
}

std::ostream& operator<< (std::ostream& out, AdjList &list)
{
    for (unsigned i = 0; i <= list.maxVertexNum; ++i)
    {
        for (int j = 0; j < list.G[i].size(); ++j)
        {
            out << i << ' ' << list.G[i][j].second << ' ' << list.G[i][j].first << '\n'; 
        }
    }
    return out;
}

#endif	/* ADJLIST_HPP */
