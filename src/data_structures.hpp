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
    std::vector< std::vector< std::pair<int, unsigned> > > G;
    void addEdgeForJohnson(Edge edge);
public:
    int maxVertexNum;
    int infinity;
    
    AdjList();
    AdjList(unsigned, int);
    AdjList(std::vector< std::vector<std::pair<int, unsigned> > > g);
    ~AdjList();
    
    void resize(unsigned);
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
    std::vector< std::vector < int > > G;
public:
    int maxVertexNum;
    int infinity;
    
    AdjMatrix();
    AdjMatrix(int inf) { maxVertexNum = -1; infinity = inf; }
    AdjMatrix(std::vector< std::vector< int > > g, int inf);
    AdjMatrix(unsigned, int);
    ~AdjMatrix();
    void resize(unsigned size)
    {
        G.resize(size);
        for (int i = 0; i < size; ++i)
            G[i].resize(size);
        maxVertexNum = (int)size - 1; 
    }
    int addEdge(Edge edge);
    int deleteEdge(unsigned, unsigned);
    void clear();
    
    void toAdjList(AdjList&);
    void toEdgeList(EdgeList&);
    
    std::vector<int>& operator [](int);
    
    friend std::istream& operator>> (std::istream& in, AdjMatrix& matr);
    friend std::ostream& operator<< (std::ostream& out, AdjMatrix& matr);

    // Parallel Floyd Algorithm
    void ParallelFloyd(std::vector< std::vector< int > >& PathMatrix);
};

class EdgeList
{
    std::vector<Edge> edgeList;
public:
    int maxVertexNum;
    int infinity;
    EdgeList() {}
    EdgeList(std::vector<Edge> edgeList);
    ~EdgeList();
    void resize(unsigned);
    int addEdge(Edge);
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
    // Integer overflow possible
    int cost();
};

#endif	/* DATA_STRUCTURES_HPP */
