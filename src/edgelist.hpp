/* 
 * File:   edgelist.hpp
 * Author: svyat
 *
 * Created on March 31, 2014, 1:07 AM
 */

#ifndef EDGELIST_HPP
#define	EDGELIST_HPP

#include <vector>
#include <limits.h>
#include <algorithm>
#include "edge.hpp"
#include "data_structures.hpp"

EdgeList::EdgeList()
{
    maxVertexNum = -1;
    infinity = INT_MAX;
    directed = false;
}

EdgeList::EdgeList(bool directed)
{
    maxVertexNum = -1;
    infinity = INT_MAX;
    this->directed = directed;
}

EdgeList::EdgeList(std::vector<Edge> edgeList, int inf, bool directed) : edgeList(edgeList)
{
    maxVertexNum = -1;
    infinity = inf;
    this->directed = directed;
    for (int i = 0; i < edgeList.size(); ++i)
        if (maxVertexNum < std::max(edgeList[i].u, edgeList[i].v))
            maxVertexNum = std::max(edgeList[i].u, edgeList[i].v);
}

EdgeList::~EdgeList()
{
    clear();
}

int EdgeList::addEdge(Edge edge, bool checkExistance)
{
    if (!directed && edge.u > edge.v)
        std::swap(edge.u, edge.v);
    if (checkExistance)
        for (int i = 0; i < edgeList.size(); ++i)
            if (edgeList[i].u == edge.u && edgeList[i].v == edge.v)
                return 1;
    edgeList.push_back(edge);
    if (std::max(edge.u, edge.v) > maxVertexNum)
        maxVertexNum = std::max(edge.u, edge.v);
    return 0;
}

int EdgeList::deleteEdge(unsigned u, unsigned v)
{
    // Need to recalc maxvertexnum!!!
    if (u > maxVertexNum || v > maxVertexNum || u == v)
        return 1;
    if (!directed && u > v)
        std::swap(u, v);
    for (int i = 0; i < edgeList.size(); ++i)
    {
        if (edgeList[i].u == u && edgeList[i].v == v)
        {
            for (int j = i; j + 1 < edgeList.size(); ++j)
                edgeList[j] = edgeList[j + 1];
            edgeList.pop_back();
            return 0;
        }
    }
    return 1;
}

void EdgeList::clear()
{
    edgeList.clear();
    maxVertexNum = -1;
}

void EdgeList::toAdjList(AdjList &g)
{
    g.resize(maxVertexNum + 1);
    g.infinity = infinity;
    g.maxVertexNum = maxVertexNum;
    g.directed = directed;
    for (int i = 0; i < edgeList.size(); ++i)
    {
        if (!directed && edgeList[i].u < edgeList[i].v)
            g.addEdge(edgeList[i], false);
        else if (directed)
            g.addEdge(edgeList[i], false);
    }
}

void EdgeList::toAdjMatrix(AdjMatrix &g)
{
    g.resize(maxVertexNum + 1);
    g.maxVertexNum = maxVertexNum;
    g.infinity = infinity;
    g.directed = directed;
    for (int i = 0; i <= maxVertexNum; ++i)
        for (int j = i + 1; j <= maxVertexNum; ++j)
            g.addEdge(Edge(i, j, infinity));
    for (int i = 0; i < edgeList.size(); ++i)
        g.addEdge(edgeList[i]);
}

int EdgeList::size()
{
    return edgeList.size();
}

void EdgeList::resize(unsigned size)
{
    for (int i = (int)edgeList.size() - 1; i > -1; --i)
    {
        if (std::max(edgeList[i].u, edgeList[i].v) >= size)
        {
            for (int j = i; j + 1 < edgeList.size(); ++j)
                edgeList[j] = edgeList[j + 1];
            edgeList.pop_back();
        }
    }
    maxVertexNum = (int)size - 1;
}

Edge &EdgeList::operator [](int i)
{
    return edgeList[i];
}

int EdgeList::cost()
{
    int cost = 0;
    for (int i = 0; i < edgeList.size(); ++i)
        cost += edgeList[i].weight;
    return cost;
}

std::istream& operator>> (std::istream& in, EdgeList &list)
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

std::ostream& operator<< (std::ostream& out, EdgeList &list)
{
    for (int i = 0; i < list.size(); ++i)
        out << list[i] << '\n';
    return out;
}

#endif	/* EDGELIST_HPP */

