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
    void deleteEdge(unsigned FirstVertexNum, unsigned SecondVertexNum);
    void sort() { std::sort(begin(), end()); }
    iterator begin() { return edgeList.begin(); }
    iterator end() { return edgeList.end(); }
    // Integer overflow possible
    int cost();
    friend std::ostream& operator<< (std::ostream& out, EdgeList &list);
};

void EdgeList::addEdge(Edge edge)
{
    edgeList.push_back(edge);
    if (std::max(edge.u, edge.v) > maxVertexNum)
        maxVertexNum = std::max(edge.u, edge.v);
}

void EdgeList::deleteEdge(unsigned FirstVertexNum, unsigned SecondVertexNum)
{
    int i;
    if (FirstVertexNum > maxVertexNum || SecondVertexNum > maxVertexNum || FirstVertexNum == SecondVertexNum)
        throw "This edge not exists!";
    for (i = 0; i < edgeList.size(); ++i)
        if (FirstVertexNum == edgeList[i].u && SecondVertexNum == edgeList[i].v)
        {
            for (int j = i + 1; j < edgeList.size(); ++j)
                edgeList[j - 1] = edgeList[j];
            break;
        }
    if (i == edgeList.size())
        throw "This edge not exists!";
    edgeList.pop_back();
}

int EdgeList::cost()
{
    int cost = 0;
    for (iterator it = begin(); it != end(); ++it)
        cost += it->weight;
    return cost;
}

std::ostream& operator<< (std::ostream& out, EdgeList &list)
{
    unsigned i;
    for (i = 0; i < list.edgeList.size(); ++i)
    {
        out << list.edgeList[i].u << ' ' << list.edgeList[i].v << ' ' << list.edgeList[i].weight << '\n';
    }
    if (i != list.edgeList.size())
        throw "Writing error!";
    return out;
}

#endif	/* EDGELIST_HPP */

