/* 
 * File:   main.cpp
 * Author: svyat
 *
 * Created on June 1, 2014, 10:30 PM
 */

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/floyd_warshall_shortest.hpp>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS, no_property,
        property< edge_weight_t, int, property< edge_weight2_t, int> > > Graph;
typedef pair<int, int> Edge;

int n, m;
Edge *e;
int *weights;
vector<Edge> mst;
int **D;

int main(int argc, char** argv) {
    freopen("input.txt", "r", stdin);
    freopen("Boost.txt", "w", stdout);
    scanf("%d %d", &n, &m);
    e = new Edge[m];
    weights = new int[m];
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &e[i].first, &e[i].second, &weights[i]);
    }
    Graph g(e, e + m, n);
    property_map < Graph, edge_weight_t >::type weight = get(edge_weight, g);
    int *wp = weights;
    graph_traits<Graph>::edge_iterator e, e_end;
    for (boost::tie(e, e_end) = edges(g); e != e_end; ++e)
        weight[*e] = *wp++;
    vector<int>d(n, (numeric_limits<int>::max)());
    D = new int*[n];
    for (int i = 0; i < n; ++i)
        D[i] = new int[n];
    floyd_warshall_all_pairs_shortest_paths(g, D, distance_map(&d[0]));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            if (D[i][j] == (numeric_limits<int>::max)())
                printf("inf ");
            else printf("%d ", D[i][j]);
        puts("");
    }
    return 0;
}
