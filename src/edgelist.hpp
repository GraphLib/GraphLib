/* 
 * File:   edgelist.hpp
 * Author: svyat, alex
 *
 * Created on March 31, 2014, 1:07 AM
 */

#ifndef EDGELIST_HPP
#define	EDGELIST_HPP

#include <vector>
#include <algorithm>
#include "edge.hpp"
#include "data_structures.hpp"

EdgeList::EdgeList(std::vector<Edge> edgeList) : edgeList(edgeList)
{
    maxVertexNum = -1;
    for (int i = 0; i < edgeList.size(); ++i)
        if (maxVertexNum < std::max(edgeList[i].u, edgeList[i].v))
            maxVertexNum = std::max(edgeList[i].u, edgeList[i].v);
}

EdgeList::~EdgeList()
{
    clear();
}

int EdgeList::addEdge(Edge edge)
{
    edgeList.push_back(edge);
    std::swap(edge.u, edge.v);
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
    int deleted = 0;
    for (int i = 0; deleted != 2 && i < edgeList.size(); ++i)
    {
        if (std::min(edgeList[i].u, edgeList[i].v) == u &&
                std::max(edgeList[i].u, edgeList[i].v) == v)
        {
            for (int j = i; j + 1 < edgeList.size(); ++j)
                edgeList[j] = edgeList[j + 1];
            edgeList.pop_back();
            ++deleted;
        }
        else if (std::min(edgeList[i].u, edgeList[i].v) == v &&
                std::max(edgeList[i].u, edgeList[i].v) == u)
        {
            for (int j = i; j + 1 < edgeList.size(); ++j)
                edgeList[j] = edgeList[j + 1];
            edgeList.pop_back();
            ++deleted;
        }
    }
    if (deleted != 2)
        return 1;
    return 0;
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
    for (int i = 0; i < edgeList.size(); ++i)
        if (edgeList[i].u < edgeList[i].v)
            g.addEdge(edgeList[i], false);
}

void EdgeList::toAdjMatrix(AdjMatrix &g)
{
    g.resize(maxVertexNum + 1);
    g.maxVertexNum = maxVertexNum;
    g.infinity = infinity;
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

