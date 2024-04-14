#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <fstream>
#include "Graph.h"
#include "Parcer.h"
#include "Solver.h"

using namespace std;
int main() {
    char filename[20];
    cin >> filename;
    Parcer parcer(filename);
    parcer.parseFile(filename);
    int V = parcer.get_V();
    Graph g(V);
    int E = parcer.get_E();
    vector<pair<int, int>> edges = parcer.get_edges();
    for (int i = 0; i < E; i++){
        g.addEdge(edges[i].first, edges[i].second);
    }
    Solver solver;
    solver.GreedyColoring(V, g);
    return 0;
}