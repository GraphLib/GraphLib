/* 
 * File:   main.cpp
 * Author: svyat
 *
 * Created on June 1, 2014, 10:30 PM
 */

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <limits.h>
#include "../../src/all_shortest_paths.hpp"
#include "../../src/graph.hpp"
#include "../../src/edge.hpp"
using namespace std;

int n, m;
vector< vector<int> > d, p;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("GraphLib.txt", "w", stdout);
    scanf("%d %d", &n, &m);
    Graph g(n, true);
    Edge e;
    for (int i = 0; i < m; ++i) {
      cin >> e;
      g.addEdge(e);
    }
    ParallelJohnson(g, d, p);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j)
	if (d[i][j] == INT_MAX)
	  printf("inf ");
	else printf("%d ", d[i][j]);
      puts("");
    }
    return 0;
}
