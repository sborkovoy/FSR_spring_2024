

#include "Solver.h"
#include "Graph.h"

using namespace std;


void Solver::GreedyColoring(int V, Graph &g) {
    int result[V];
    result[0] = 0;
    for (int i = 1; i < V; i++) {
        result[i] = -1;
    }
    bool available[V];
    for (int i = 0; i < V; i++) {
        available[i] = false;
    }

    vector<pair<int, int>> degrees;
    for (int i = 0; i < V; i++) {
        degrees.push_back({g.getAdj(i).size(), i});
    }
    sort(degrees.begin(), degrees.end(), greater<pair<int, int>>());

    for (int i = 0; i < V; i++) {
        int vertex = degrees[i].second;
        list<int> &Adj = g.getAdj(vertex);
        list<int>::iterator it;
        for (it = Adj.begin(); it != Adj.end(); ++it) {
            if (result[*it] != -1) {
                available[result[*it]] = true;
            }
        }
        int cr;
        for (cr = 0; cr < V; cr++)
            if (available[cr] == false)
                break;

        result[vertex] = cr;
        for (it = Adj.begin(); it != Adj.end(); ++it)
            if (result[*it] != -1)
                available[result[*it]] = false;
    }

    for (int k = 0; k < V; k++)
        cout << " " << result[k] + 1;
}