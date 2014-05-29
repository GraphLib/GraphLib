/* 
 * File:   edge.hpp
 * Author: svyat
 *
 * Created on March 31, 2014, 1:19 AM
 */

#ifndef EDGE_HPP
#define	EDGE_HPP

/**
 * Edge - class for edge of graph
 */
class Edge
{
public:
    // first vertex
    unsigned u;
    // second vertex
    unsigned v;
    // weight
    int weight;
    
    Edge() {}
    /**
     * Constructor
     * @param u - first vertex of graph
     * @param v - second vertex of graph
     * @param weight - weight
     */
    Edge(unsigned u, unsigned v, int weight) : u(u), v(v), weight(weight) {}
    bool operator<(Edge other) const
    {
        return weight < other.weight;
    }
    friend std::istream& operator>> (std::istream&, Edge &);
    friend std::ostream& operator<< (std::ostream&, Edge &);
};

std::istream& operator>> (std::istream& in, Edge &edge)
{
    in >> edge.u >> edge.v >> edge.weight;
    return in;
}

std::ostream& operator<< (std::ostream& out, Edge &edge)
{
    out << edge.u << " " << edge.v << " " << edge.weight;
    return out;
}

#endif	/* EDGE_HPP */
