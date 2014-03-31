/* 
 * File:   vertexlist.hpp
 * Author: svyat
 *
 * Created on March 31, 2014, 2:07 PM
 */

#ifndef VERTEXLIST_HPP
#define	VERTEXLIST_HPP

class VertexList
{
    std::vector<unsigned> vertexList;
public:
    typedef std::vector<unsigned>::iterator iterator;
    VertexList() {}
    VertexList(std::vector<unsigned> vertexList) : vertexList(vertexList) {}
    VertexList(std::vector<int> predecessor, int start, int finish)
    {
        if (predecessor[finish] != -1)
        {
            int tmp = finish;
            while (tmp != start)
            {
                addVertex(tmp);
                tmp = predecessor[tmp];
            }
            addVertex(start);
            std::reverse(begin(), end());
        }
    }
    /*VertexList(AdjList)
    {
        //
    }*/
    ~VertexList()
    {
        vertexList.clear();
    }
    void addVertex(unsigned vertex) { vertexList.push_back(vertex); }
    iterator begin() { return vertexList.begin(); }
    iterator end() { return vertexList.end(); }
    unsigned size() { return vertexList.size(); }
    friend std::ostream& operator<< (std::ostream& out, VertexList& list);
};

std::ostream& operator<< (std::ostream& out, VertexList& list)
{
    for (VertexList::iterator it = list.begin(); it != list.end(); ++it)
        out << *it << " ";
    return out;
}

#endif	/* VERTEXLIST_HPP */

