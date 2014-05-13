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
}

AdjList::AdjList(unsigned size, int infinity)
{
    this->maxVertexNum = (int)size - 1;
    G.resize(size);
    this->infinity = infinity;
}

AdjList::AdjList(std::vector< std::vector<std::pair<int, unsigned> > > g)
{
    G = g;
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

void AdjList::resize(unsigned size)
{
    G.resize(size);
    maxVertexNum = size - 1;
}

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
    G[edge.v].push_back(std::make_pair(edge.weight, edge.u));
    return 0;
}

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
            return 1;
        }
    }
    return 1;
}

void AdjList::clear()
{
    for (int i = 0; i < G.size(); ++i)
        G[i].clear();
    G.clear();
    maxVertexNum = -1;
}

void AdjList::toAdjMatrix(AdjMatrix &g)
{
    g.resize(maxVertexNum + 1);
    g.maxVertexNum = maxVertexNum;
    g.infinity = infinity;
    for (int i = 0; i <= maxVertexNum; ++i)
    {
        for (int j = i + 1; j <= maxVertexNum; ++j)
        {
            g.addEdge(Edge(i, j, infinity));
            g.addEdge(Edge(j, i, infinity));
        }
    }
    for (unsigned i = 0; i < G.size(); ++i)
        for (int j = 0; j < G[i].size(); ++j)
            g.addEdge(Edge(i, G[i][j].second, G[i][j].first));
}

void AdjList::toEdgeList(EdgeList &g)
{
    g.maxVertexNum = maxVertexNum;
    g.infinity = infinity;
    for (unsigned i = 0; i < G.size(); ++i)
        for (int j = 0; j < G[i].size(); ++j)
            if (i < G[i][j].second)
                g.addEdge(Edge(i, G[i][j].second, G[i][j].first));
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
