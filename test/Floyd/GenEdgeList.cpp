/**
 * This program generates graph (directed or undirected) in edge list
 * With vertices. Vertices numbered form 0 to "n - 1"
 * Graph contains "m" edges with weights from "minW" to "maxW"
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <set>
using namespace std;

const int n = 4; // number of vertices;
const int m = 5; // number of edges;
const int minW = -1; // minimal weight of edge;
const int maxW = 100; // maximal weight of edge;
bool directed = true; // obvious
set< pair<int, int> > exist;

int generateWeight() {
  return rand() % (maxW - minW + 1) + minW;
}

int main() {
  if (directed) {
    if (n *1ll* (n - 1) < m) {
      fprintf(stderr, "Too many edges for directed graph!\nAmount of edges should not exceed n * (n - 1)\n");
      return 1;
    }
  }
  else {
    if (n * 1ll * (n - 1) / 2 < m) {
      fprintf(stderr, "Too many edges for undirected graph!\nAmount of edges should not exceed n * (n - 1) / 2\n");
      return 1;
    }
  }
  if (n == 0) {
    fprintf(stderr, "Amount of edges should be positive!\n");
    return 1;
  }
  freopen("input.txt", "w", stdout);
  srand(time(NULL));
  printf("%d %d\n", n, m);
  pair<int, int> e;
  for (int i = 0, w; i < m; ++i) {
    do {
      e.first = rand() % n; // generates first vertex of edge
      e.second = rand() % n; // generates second vertex of edge
      if (!directed && e.first > e.second)
	swap(e.first, e.second);
    } while (e.first == e.second || exist.find(e) != exist.end()); // Edge is loop or this edge has been generated
    exist.insert(e);
    w = generateWeight();
    printf("%d %d %d\n", e.first, e.second, w);
  }
  if (exist.size() != m)
    fprintf(stderr, "Something wrong with generating edges!\n");
  return 0;
}
