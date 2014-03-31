/* 
 * File:   edgelist.hpp
 * Author: svyat
 *
 * Created on March 31, 2014, 1:07 AM
 */

#ifndef EDGELIST_HPP
#define	EDGELIST_HPP

#include <vector>
#include <algorithm>
#include "edge.hpp"
#include "adjlist.hpp"

class EdgeList
{
    std::vector<Edge> edgeList;
public:
    typedef std::vector<Edge>::iterator iterator;
    int maxVertexNum;
    EdgeList() {}
    EdgeList(std::vector<Edge> edgeList) : edgeList(edgeList)
    {
        maxVertexNum = -1;
        for (iterator it = begin(); it != end(); ++it)
            if (maxVertexNum < std::max(it->u, it->v))
                maxVertexNum = std::max(it->u, it->v);
    }
    /*EdgeList(AdjList g)
    {
        unsigned n = g.maxVertexNum;
        for (unsigned i = 0; i <= n; ++i)
        {
            for (AdjList::iterator it = g.begin(i); it != g.end(i); ++it)
            {
                edgeList.push_back(Edge(i, it->second, it->first));
                if (maxVertexNum < std::max(it->second, i))
                    maxVertexNum = std::max(it->second, i);                  
            }
        }
    }*/
    ~EdgeList()
    {
        edgeList.clear();
    }
    void addEdge(Edge edge);
    void sort() { std::sort(begin(), end()); }
    iterator begin() { return edgeList.begin(); }
    iterator end() { return edgeList.end(); }
    // Integer overflow possible
    int cost();
};

void EdgeList::addEdge(Edge edge)
{
    edgeList.push_back(edge);
    if (std::max(edge.u, edge.v) > maxVertexNum)
        maxVertexNum = std::max(edge.u, edge.v);
}

int EdgeList::cost()
{
    int cost = 0;
    for (iterator it = begin(); it != end(); ++it)
        cost += it->weight;
    return cost;
}

#endif	/* EDGELIST_HPP */

