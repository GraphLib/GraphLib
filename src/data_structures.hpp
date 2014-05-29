/* 
 * File:   data_structures.hpp
 * Author: svyat
 *
 * Created on May 4, 2014, 3:17 AM
 */

#ifndef DATA_STRUCTURES_HPP
#define	DATA_STRUCTURES_HPP

class AdjList;
class AdjMatrix;
class EdgeList;

/**
 * AdjList - class for adjacency list
 */
class AdjList
{
    // Graph (Adjacency List)
    std::vector< std::vector< std::pair<int, unsigned> > > G;
    // Add Edge (no check existence of vertices)
    void addEdgeForJohnson(Edge edge);
public:
    // Last vertex number
    int maxVertexNum;
    // Designation of infinity
    int infinity;
    // Existence of edge direction
    bool directed;
    
    AdjList();
    AdjList(bool);
    AdjList(unsigned, int, bool);
    AdjList(std::vector< std::vector<std::pair<int, unsigned> > >, bool);
    ~AdjList();
    
    // change number of vertices
    void resize(unsigned);
    // add vertex
    void addVertex();
    // add edge
    int addEdge(Edge, bool);
    // delete edge
    int deleteEdge(unsigned, unsigned);
    // clear
    void clear();
    
    // convert to adjacency matrix
    void toAdjMatrix(AdjMatrix&);
    // convert to edge list
    void toEdgeList(EdgeList&);
    
    std::vector< std::pair<int, unsigned> >& operator [](int i);
    
    friend std::istream& operator>> (std::istream& in, AdjList &list);
    friend std::ostream& operator<< (std::ostream& out, AdjList &list);
};

/**
 * AdjList - class for adjacency matrix
 */
class AdjMatrix
{
     // Graph (Adjacency Matrix)
    std::vector< std::vector < int > > G;
public:
    // Last vertex number
    int maxVertexNum;
    // Designation of infinity
    int infinity;
    // Existence direction edges
    bool directed;
    
    AdjMatrix();
    AdjMatrix(bool);
    AdjMatrix(std::vector< std::vector< int > >, int, bool);
    AdjMatrix(unsigned, int, bool);
    ~AdjMatrix();
    
    // change number of vertices
    void resize(unsigned size);
    // add vertex
    void addVertex();
    // add edge
    int addEdge(Edge edge);
    // delete edge
    int deleteEdge(unsigned, unsigned);
    // clear
    void clear();
    
    // convert to adjacency list
    void toAdjList(AdjList&);
    // convert to edge list
    void toEdgeList(EdgeList&);
    
    std::vector<int>& operator [](int);
    
    friend std::istream& operator>> (std::istream& in, AdjMatrix& matr);
    friend std::ostream& operator<< (std::ostream& out, AdjMatrix& matr);
};

/**
 * AdjList - class for edge list
 */
class EdgeList
{
    // Graph (Edge List)
    std::vector<Edge> edgeList;
public:
    // Last vertex number
    int maxVertexNum;
    int infinity;
    bool directed;
    
    EdgeList();
    EdgeList(bool);
    EdgeList(std::vector<Edge>, int, bool);
    ~EdgeList();
    
    void resize(unsigned);
    void addVertex();
    int addEdge(Edge, bool);
    int deleteEdge(unsigned, unsigned);
    void clear();
    
    void toAdjList(AdjList&);
    void toAdjMatrix(AdjMatrix&);
    
    int size();
    void resize();
    
    Edge & operator [](int i);
    
    friend std::istream& operator>> (std::istream& in, EdgeList &list);
    friend std::ostream& operator<< (std::ostream& out, EdgeList &list);
    
    //void sort() { std::sort(edgeList.begin(), edgeList.end()); }
    int cost();
};

#endif	/* DATA_STRUCTURES_HPP */
