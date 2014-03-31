/* 
 * File:   mst.hpp
 * Author: svyat
 *
 * Created on March 31, 2014, 12:56 PM
 */

#ifndef MST_HPP
#define	MST_HPP

#include "edgelist.hpp"
#include "dsu.hpp"

int kruskal(EdgeList g, EdgeList& mst)
{
    int cost = 0;
    DSU dsu(g.maxVertexNum);
    g.sort();
    for (EdgeList::iterator it = g.begin(); it != g.end(); ++it)
    {
        if (dsu.unite(it->u, it->v))
        {
            mst.addEdge(*it);
            cost += it->weight;
        }
    }
    return cost;
}

#endif	/* MST_HPP */

