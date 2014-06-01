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

/**
 * Constructor
 */
EdgeList::EdgeList()
{
    maxVertexNum = -1;
    infinity = INT_MAX;
    directed = true;
}

/**
 * Constructor
 * @param directed - true, if edges are directed
 */
EdgeList::EdgeList(bool directed)
{
    maxVertexNum = -1;
    infinity = INT_MAX;
    this->directed = directed;
}

/**
 * Constructor
 * @param edgeList - edge list
 * @param infinity - designation of infinity (if edge doesn't exist)
 * @param directed - true, if edges are directed, and false - otherwise
 */
EdgeList::EdgeList(std::vector<Edge> edgeList, int inf, bool directed):
    edgeList(edgeList)
{
    maxVertexNum = -1;
    infinity = inf;
    this->directed = directed;
    for (int i = 0; i < edgeList.size(); ++i)
        if (maxVertexNum < std::max(edgeList[i].u, edgeList[i].v))
            maxVertexNum = std::max(edgeList[i].u, edgeList[i].v);
}

/**
 * Destructor
 */
EdgeList::~EdgeList()
{
    clear();
}

/**
 * addEdge() - adds edge
 * @param edge - new edge
 * @param checkExistence - true, if it needs to check existence of edge,
 * false - otherwise
 * @return 0, if edge was added, and 1, otherwise
 */
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

/**
 * deleteEdge() - removes the edge
 * @param u - first vertex of edge
 * @param v - second vertex of edge
 * @return 0, if edge was deleted, and 1, otherwise
 */
int EdgeList::deleteEdge(unsigned u, unsigned v)
{
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

/**
 * clear() - clears graph
 */
void EdgeList::clear()
{
    edgeList.clear();
    maxVertexNum = -1;
}

/**
 * toAdjList() - converts graph (edge list) to adjacency list
 * @param g - adjacency list for this graph 
 */
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

/**
 * toAdjMatrix() - converts graph (edge list) to adjacency matrix
 * @param g - adjacency matrix for this graph 
 */
void EdgeList::toAdjMatrix(AdjMatrix &g)
{
    g.resize(maxVertexNum + 1);
    g.maxVertexNum = maxVertexNum;
    g.infinity = infinity;
    g.directed = directed;
    for (int i = 0; i <= maxVertexNum; ++i)
        for (int j = i + 1; j <= maxVertexNum; ++j)
            g.addEdge(Edge(i, j, infinity), false);
    for (int i = 0; i < edgeList.size(); ++i)
        g.addEdge(edgeList[i], false);
}

/**
 * @return number of edges in edge list
 */
int EdgeList::size()
{
    return edgeList.size();
}

/**
 * resize() - changes number of vertices
 * @param size - new number of vertices
 */
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

/**
 * @return iterator to the first element of edge list
 */
std::vector<Edge>::iterator EdgeList::begin()
{
    return edgeList.begin();
}

Edge &EdgeList::operator [](int i)
{
    return edgeList[i];
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

