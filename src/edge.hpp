/* 
 * File:   edge.hpp
 * Author: svyat
 *
 * Created on March 31, 2014, 1:19 AM
 */

#ifndef EDGE_HPP
#define	EDGE_HPP

class Edge
{
public:
    unsigned u;
    unsigned v;
    int weight;
    Edge() {}
    Edge(unsigned u, unsigned v, int weight) : u(u), v(v), weight(weight) {}
    bool operator<(Edge other) const
    {
        return weight < other.weight;
    }
    friend std::istream& operator>> (std::istream& in, Edge &edge);
};

std::istream& operator>> (std::istream& in, Edge &edge)
{
    in >> edge.u >> edge.v >> edge.weight;
    return in;
}

#endif	/* EDGE_HPP */

