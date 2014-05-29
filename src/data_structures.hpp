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

class AdjList
{
    // Graph (Adjacency List)
    std::vector< std::vector< std::pair<int, unsigned> > > G;
    // Add Edge (no check existence of vertices)
    void addEdgeForJohnson(Edge edge);
public:
    // Last vertex number
    int maxVertexNum;
    int infinity;
    bool directed;
    
    AdjList();
    AdjList(bool);
    AdjList(unsigned, int, bool);
    AdjList(std::vector< std::vector<std::pair<int, unsigned> > >, bool);
    ~AdjList();
    
    void resize(unsigned);
    void addVertex();
    int addEdge(Edge, bool);
    int deleteEdge(unsigned, unsigned);
    void clear();
    
    void toAdjMatrix(AdjMatrix&);
    void toEdgeList(EdgeList&);
    
    std::vector< std::pair<int, unsigned> >& operator [](int i);
    
    friend std::istream& operator>> (std::istream& in, AdjList &list);
    friend std::ostream& operator<< (std::ostream& out, AdjList &list);
};

class AdjMatrix
{
     // Graph (Adjacency Matrix)
    std::vector< std::vector < int > > G;
public:
    // Last vertex number
    int maxVertexNum;
    int infinity;
    bool directed;
    
    AdjMatrix();
    AdjMatrix(bool);
    AdjMatrix(std::vector< std::vector< int > >, int, bool);
    AdjMatrix(unsigned, int, bool);
    ~AdjMatrix();
    
    void resize(unsigned size);
    void addVeretex();
    int addEdge(Edge edge);
    int deleteEdge(unsigned, unsigned);
    void clear();
    
    void toAdjList(AdjList&);
    void toEdgeList(EdgeList&);
    
    std::vector<int>& operator [](int);
    
    friend std::istream& operator>> (std::istream& in, AdjMatrix& matr);
    friend std::ostream& operator<< (std::ostream& out, AdjMatrix& matr);
};

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
    void addVeretex();
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
