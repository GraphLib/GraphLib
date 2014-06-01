/**
 * This program checks equality of MST cost between Boost and GraphLib
 */

#include <iostream>
#include <cstdio>
using namespace std;

int main() {
  int BoostCost = 0;
  int GraphLibCost = 0;
  freopen("BoostKruskal.txt", "r", stdin);
  int u, v, w;
  while (scanf("%d %d %d", &u, &v, &w) == 3) {
    BoostCost += w;
  }
  freopen("GraphLibKruskal.txt", "r", stdin);
  while (scanf("%d %d %d", &u, &v, &w) == 3) {
    GraphLibCost += w;
  }
  if (BoostCost == GraphLibCost)
    puts("Correct");
  else printf("Incorrect: Boost result - (%d), GraphLib result - (%d)\n",
	      BoostCost, GraphLibCost);
  return 0;
}
