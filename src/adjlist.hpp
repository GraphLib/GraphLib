/* 
 * File:   adjlist.hpp
 * Author: svyat, alex
 *
 * Created on March 31, 2014, 2:02 AM
 */

#ifndef ADJLIST_HPP
#define	ADJLIST_HPP

#include <vector>
#include "edgelist.hpp"
#include "edge.hpp"

class AdjList
{
    std::vector< std::vector< std::pair<int, unsigned> > > G;
public:
    typedef std::vector<std::pair<int, unsigned> >::iterator iterator;
    int maxVertexNum;
    AdjList() { maxVertexNum = -1; infinity = -1;}
    AdjList(std::vector< std::vector<std::pair<int, unsigned> > > g);
    //AdjList(EdgeList g);
    ~AdjList()
    {
        for (int i = 0; i < G.size(); ++i)
            G[i].clear();
        G.clear();
    }
    void resize(unsigned size) { G.resize(size); }
    void addEdge(Edge edge);
    void addVertex();
    AdjMatrix toAdjMatrix();
    iterator begin(unsigned u) { return (u >= G.size()) ? G[0].begin() : G[u].begin(); }
    iterator end(unsigned u) { return (u >= G.size()) ? G[0].begin() : G[u].end(); }
    friend std::istream& operator>> (std::istream& in, AdjList &list);
    friend std::ostream& operator<< (std::ostream& out, AdjList &list);
};

AdjList::AdjList(std::vector< std::vector<std::pair<int, unsigned> > > g)
{
    G = g;
    maxVertexNum = -1;
    for (unsigned i = 0; i < g.size(); ++i)
        for (int j = 0; j < g[i].size(); ++j)
            if (maxVertexNum < std::max(g[i][j].second, i))
                maxVertexNum = std::max(g[i][j].second, i);               
}

void AdjList::addVertex()
{
    maxVertexNum++;
    std::vector<std::pair<int, unsigned> > forNew;
    forNew.clear();
    G.push_back(forNew);
}

void AdjList::addEdge(Edge edge)
{
    G[edge.u].push_back(std::make_pair(edge.weight, edge.v));
    if (maxVertexNum < (int)std::max(edge.u, edge.v))
        maxVertexNum = std::max(edge.u, edge.v);    
}

AdjMatrix AdjList::toAdjMatrix()
{
    AdjMatrix g;
    g.resize(maxVertexNum + 1);
    g.maxVertexNum = maxVertexNum;
    g.infinity = infinity;
    Edge newEdge;
    for (int i = 1; i <= maxVertexNum; i++)
    {
        for (int j = 1; j <= maxVertexNum; j++)
            if (i == j)
            {
                newEdge.u = i;
                newEdge.v = j; 
                newEdge.weight = 0;
                g.addEdge(newEdge);
            }
            else
            {
                newEdge.u = i;
                newEdge.v = j; 
                newEdge.weight = infinity;
                g.addEdge(newEdge);
            }
    }
    for (unsigned i = 0; i < G.size(); ++i)
        for (int j = 0; j < G[i].size(); ++j)
        {
            newEdge.u = i; 
            newEdge.v = G[i][j].second; 
            newEdge.weight = G[i][j].first; 
            g.addEdge(newEdge);
        }
    return g;
}

std::istream& operator>> (std::istream& in, AdjList &list)
{
    int n, m;
    in >> n >> m;
    list.resize(n + 1);
    Edge edge;
    for (int i = 0; i < m; ++i)
    {
        in >> edge;
        list.addEdge(edge);
        /* in case of graph is undirected
        std::swap(edge.u, edge.v);
        list.addEdge(edge);
         */
    }
    return in;
}

std::ostream& operator<< (std::ostream& out, AdjList &list)
{
    for (unsigned i = 0; i < list.maxVertexNum; ++i)
    {
        for (AdjList::iterator it = list.begin(i); it != list.end(i); ++it)
        {
            out << i << ' ' << it->second << ' ' << it->first << '\n'; 
        }
    }
    return out;
}

#endif	/* ADJLIST_HPP */
