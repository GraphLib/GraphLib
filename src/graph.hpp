/* 
 * File:   graph.hpp
 * Author: svyat
 *
 * Created on May 4, 2014, 12:33 AM
 */

#ifndef GRAPH_HPP
#define	GRAPH_HPP

#include <assert.h>
#include <limits.h>
#include "adjlist.hpp"
#include "adjmatrix.hpp"
#include "edgelist.hpp"

enum Type { ADJLIST, ADJMATRIX, EDGELIST };

class Graph
{
    void AdjListToAdjMatrix();
    void AdjListToEdgeList();
    void AdjMatrixToAdjList();
    void AdjMatrixToEdgeList();
    void EdgeListToAdjList();
    void EdgeListToAdjMatrix();
public:
    AdjList adjList;
    AdjMatrix adjMatrix;
    EdgeList edgeList;
    Type currentType;
    int infinity;
    
    Graph();
    Graph(unsigned);
    Graph(AdjList);
    Graph(AdjMatrix);
    Graph(EdgeList);
    ~Graph();
    
    void resize(unsigned);
    int addEdge(Edge);
    int deleteEdge(unsigned, unsigned);
    int verticesCount();
    
    void output();
    
    bool isAdjList();
    bool isAdjMatrix();
    bool isEdgeList();
    
    void toAdjList();
    void toAdjMatrix();
    void toEdgeList();    
};

Graph::Graph()
{
    currentType = ADJLIST;
    infinity = INT_MAX;
    adjList = AdjList(0, infinity);
}

Graph::Graph(unsigned size)
{
    currentType = ADJLIST;
    infinity = INT_MAX;
    adjList = AdjList(size, infinity);
}

Graph::Graph(AdjList g)
{
    currentType = ADJLIST;
    infinity = INT_MAX;
    adjList = g;
}

Graph::Graph(AdjMatrix g)
{
    currentType = ADJMATRIX;
    infinity = INT_MAX;
    adjMatrix = g;
}

Graph::Graph(EdgeList g)
{
    currentType = EDGELIST;
    edgeList = g;
}

Graph::~Graph()
{
}

void Graph::resize(unsigned size)
{
    if (isAdjList())
        adjList.resize(size);
    else if (isAdjMatrix())
        adjMatrix.resize(size);
    else if (isEdgeList())
        edgeList.resize(size);
    else assert(false);    
}

int Graph::addEdge(Edge e)
{
    if (isAdjList())
        return adjList.addEdge(e, false);
    else if (isAdjMatrix())
        return adjMatrix.addEdge(e);
    else if (isEdgeList())
        return edgeList.addEdge(e);
    else assert(false);
    return 1;
}

int Graph::deleteEdge(unsigned u, unsigned v)
{
    if (isAdjList())
        return adjList.deleteEdge(u, v);
    else if (isAdjMatrix())
        return adjMatrix.deleteEdge(u, v);
    else if (isEdgeList())
        return edgeList.deleteEdge(u, v);
    else assert(false);
    return 1;
}

int Graph::verticesCount()
{
    if (isAdjList())
        return adjList.maxVertexNum + 1;
    if (isAdjMatrix())
        return adjMatrix.maxVertexNum + 1;
    return edgeList.maxVertexNum + 1;
}

void Graph::output()
{
    if (isAdjList())
        std::cout << adjList;
    else if (isAdjMatrix());
    else std::cout << edgeList;
}

bool Graph::isAdjList()
{
    return currentType == ADJLIST;
}

bool Graph::isAdjMatrix()
{
    return currentType == ADJMATRIX;
}

bool Graph::isEdgeList()
{
    return currentType == EDGELIST;
}

void Graph::AdjListToAdjMatrix()
{
    currentType = ADJMATRIX;
    adjList.toAdjMatrix(adjMatrix);
    adjList.clear();
}

void Graph::AdjListToEdgeList()
{
    currentType = EDGELIST;
    adjList.toEdgeList(edgeList);
    adjList.clear();
}

void Graph::AdjMatrixToAdjList()
{
    currentType = ADJLIST;
    adjMatrix.toAdjList(adjList);
    adjMatrix.clear();
}

void Graph::AdjMatrixToEdgeList()
{
    currentType = EDGELIST;
    adjMatrix.toEdgeList(edgeList);
    adjMatrix.clear();
}

void Graph::EdgeListToAdjList()
{
    currentType = ADJLIST;
    edgeList.toAdjList(adjList);
    edgeList.clear();
}

void Graph::EdgeListToAdjMatrix()
{
    currentType = ADJMATRIX;
    edgeList.toAdjMatrix(adjMatrix);
    edgeList.clear();
}

void Graph::toAdjList()
{
    if (isAdjMatrix())
        AdjMatrixToAdjList();
    else if (isEdgeList())
        EdgeListToAdjList();
}

void Graph::toAdjMatrix()
{
    if (isAdjList())
        AdjListToAdjMatrix();
    else if (isEdgeList())
        EdgeListToAdjMatrix();
}

void Graph::toEdgeList()
{
    if (isAdjList())
        AdjListToEdgeList();
    else if (isAdjMatrix())
        AdjMatrixToEdgeList();
}

#endif	/* GRAPH_HPP */

