#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include "graph.hpp"
#include "all_shortest_paths.hpp"
using namespace std;

int main()
{
    Graph g(true);
    g.addEdge(Edge(0, 1, -1));
    g.addEdge(Edge(0, 4, 5));
    g.addEdge(Edge(0, 3, 4));
    g.addEdge(Edge(1, 2, 2));
    g.addEdge(Edge(2, 4, 3));
    g.addEdge(Edge(3, 4, 5));
    vector< vector<int> > d, p;
    ParallelFloyd(g, d);
    cout << "Floyd: " << endl;
    for (int i = 0; i < d.size(); ++i)
    {
        for (int j = 0; j < d[i].size(); ++j)
            cout << d[i][j] << " ";
        cout << endl;
    }
    cout << "Johnson: " << ParallelJohnson(g, d, p) << endl;
    for (int i = 0; i < d.size(); ++i)
    {
        for (int j = 0; j < d[i].size(); ++j)
            cout << d[i][j] << " ";
        cout << endl;
    }
    ParallelFloyd(g, d);
    cout << "Floyd: " << endl;
    for (int i = 0; i < d.size(); ++i)
    {
        for (int j = 0; j < d[i].size(); ++j)
            cout << d[i][j] << " ";
        cout << endl;
    }
    return 0;
}
