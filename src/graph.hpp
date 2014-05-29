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

/**
 * Types of graph representaton
 */
enum Type { ADJLIST, ADJMATRIX, EDGELIST };

/**
 * Graph - class for object graph
 */
class Graph
{
    void AdjListToAdjMatrix();
    void AdjListToEdgeList();
    void AdjMatrixToAdjList();
    void AdjMatrixToEdgeList();
    void EdgeListToAdjList();
    void EdgeListToAdjMatrix();
public:
    // Adjacency list of graph
    AdjList adjList;
    // Adjacency matrix of graph
    AdjMatrix adjMatrix;
    // Edge list of graph
    EdgeList edgeList;
    
    // Current graph representation type
    Type currentType;
    // Designation of infinity (edge's weight, if this edge doesn't exist)
    int infinity;
    // Existence of edge direction
    bool directed;
    
    Graph();
    Graph(bool);
    Graph(unsigned, bool);
    Graph(AdjList);
    Graph(AdjMatrix);
    Graph(EdgeList);
    ~Graph();
    
    // change number of vertices
    void resize(unsigned);
    // add vertex
    void addVertex();
    // add edge
    int addEdge(Edge);
    // delete edge
    int deleteEdge(unsigned, unsigned);
    // count number of vertices
    int verticesCount();
    
    // print graph
    void output();
    
    bool isAdjList();
    bool isAdjMatrix();
    bool isEdgeList();
    
    // convert graph to adjacency list
    void toAdjList();
    // convert graph to adjacency matrix
    void toAdjMatrix();
    // convert graph to edge list
    void toEdgeList();    
};

Graph::Graph()
{
    currentType = ADJLIST;
    infinity = INT_MAX;
    directed = false;
    adjList = AdjList(0, infinity, directed);
}

/**
 * Constructor
 * @param directed - true, if edges are directed
 */
Graph::Graph(bool directed)
{
    currentType = ADJLIST;
    infinity = INT_MAX;
    this->directed = directed;
    adjList = AdjList(0, infinity, directed);
}

/**
 * Constructor
 * @param size - number of vertices
 * @param directed - true, if edges are directed
 */
Graph::Graph(unsigned size, bool directed)
{
    currentType = ADJLIST;
    infinity = INT_MAX;
    this->directed = directed;
    adjList = AdjList(size, infinity, directed);
}

/**
 * Constructor
 * @param g - adjacency list of graph
 */
Graph::Graph(AdjList g)
{
    currentType = ADJLIST;
    infinity = INT_MAX;
    directed = g.directed;
    adjList = g;
}

/**
 * Constructor
 * @param g - adjacency matrix of graph
 */raph::Graph(AdjMatrix g)
{
    currentType = ADJMATRIX;
    infinity = INT_MAX;
    directed = g.directed;
    adjMatrix = g;
}

/**
 * Constructor
 * @param g - edge list of graph
 */
Graph::Graph(EdgeList g)
{
    currentType = EDGELIST;
    infinity = INT_MAX;
    directed = g.directed;
    edgeList = g;
}

Graph::~Graph()
{
}

/**
 * resize() - change number of vertices
 * @param size - new number of vertices
 */
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

/**
 * addEdge() - add edge
 * @param e - new edge
 */
int Graph::addEdge(Edge e)
{
    if (isAdjList())
        return adjList.addEdge(e, false);
    else if (isAdjMatrix())
        return adjMatrix.addEdge(e, false);
    else if (isEdgeList())
        return edgeList.addEdge(e, false);
    else assert(false);
    return 1;
}

/**
 * deleteEdge() - delete edge
 * @param u - first vertex
 * @param v - second vertex
 */
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

/**
 * verticesCount() - returns number of vertices
 */
int Graph::verticesCount()
{
    if (isAdjList())
        return adjList.maxVertexNum + 1;
    if (isAdjMatrix())
        return adjMatrix.maxVertexNum + 1;
    return edgeList.maxVertexNum + 1;
}

/**
 * output() - print graph
 */
void Graph::output()
{
    if (isAdjList())
        std::cout << adjList;
    else if (isAdjMatrix()) std::cout << adjMatrix;
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

/**
 * toAdjList() - convert graph to adjacency list 
 */
void Graph::toAdjList()
{
    if (isAdjMatrix())
        AdjMatrixToAdjList();
    else if (isEdgeList())
        EdgeListToAdjList();
}

/**
 * toAdjMatrix() - convert graph to adjacency matrix
 */
void Graph::toAdjMatrix()
{
    if (isAdjList())
        AdjListToAdjMatrix();
    else if (isEdgeList())
        EdgeListToAdjMatrix();
}

/**
 * toEdgeList() - convert graph to edge list
 */
void Graph::toEdgeList()
{
    if (isAdjList())
        AdjListToEdgeList();
    else if (isAdjMatrix())
        AdjMatrixToEdgeList();
}

#endif	/* GRAPH_HPP */

