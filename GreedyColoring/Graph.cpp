

#include "Graph.h"
using namespace std;
Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

Graph::~Graph() { delete[] adj; }

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}

list<int> &Graph::getAdj(int v) { return adj[v]; }