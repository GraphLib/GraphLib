/* 
 * File:   main.cpp
 * Author: svyat
 *
 * Created on June 1, 2014, 10:30 PM
 */

#include <cstdlib>
#include <cstdio>
#include <vector>
#include "../../mst.hpp"
#include "../../graph.hpp"
#include "../../all_shortest_paths.hpp"
#include "../../edge.hpp"
using namespace std;

int n, m;
vector<Edge> mst;

int main(int argc, char** argv) {
    freopen("input.txt", "r", stdin);
    freopen("GraphLib.txt", "w", stdout);
    scanf("%d %d", &n, &m);
    Graph g(n, false);
    g.toEdgeList();
    Edge e;
    for (int i = 0; i < m; ++i) {
      cin >> e;
      g.addEdge(e);
    }
    ParallelKruskal(g, mst);
    for (int i = 0; i < mst.size(); ++i)
      cout << mst[i] << endl;
    return 0;
}
