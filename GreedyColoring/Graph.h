
#ifndef GREEDYCOLORING_GRAPH_H
#define GREEDYCOLORING_GRAPH_H

#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <fstream>

using namespace std;

class Graph {
    int V;
    list<int> *adj;

public:
    Graph(int V);
    ~Graph();

    void addEdge(int v, int w);

    list<int> &getAdj(int v);
};



#endif //GREEDYCOLORING_GRAPH_H
