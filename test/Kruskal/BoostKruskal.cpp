/* 
 * File:   main.cpp
 * Author: svyat
 *
 * Created on June 1, 2014, 10:30 PM
 */

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/adjacency_list.hpp>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property,
        property< edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;

int n, m;
pair<int, int> *e;
int *weights;
vector<Edge> mst;

int main(int argc, char** argv) {
    freopen("input.txt", "r", stdin);
    freopen("Boost.txt", "w", stdout);
    scanf("%d %d", &n, &m);
    e = new pair<int, int>[m];
    weights = new int[m];
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &e[i].first, &e[i].second, &weights[i]);
    }
    Graph g(e, e + m, weights, n);
    property_map < Graph, edge_weight_t >::type weight = get(edge_weight, g);
    kruskal_minimum_spanning_tree(g, back_inserter(mst));
    for (vector<Edge>::iterator it = mst.begin(); it != mst.end(); ++it)
        cout << source(*it, g) << " " << target(*it, g) << " "
                << weight[*it] << '\n';
    return 0;
}
