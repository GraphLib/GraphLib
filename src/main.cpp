#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include "dijkstra.hpp"
#include "adjlist.hpp"
#include "vertexlist.hpp"
using namespace std;

int main()
{
    vector<int> p, d;
    AdjList g;
    int n, m;
    cin >> g;
    Dijkstra(g, d, p, 1, 1e9);
    VertexList path = VertexList(p, 1, g.maxVertexNum);
    if (path.size())
        cout << path << " ";
    else cout << "-1 ";
    return 0;
}
