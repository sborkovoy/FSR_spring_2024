

#ifndef GREEDYCOLORING_PARCER_H
#define GREEDYCOLORING_PARCER_H

#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <fstream>
//#include "Graph.h"

using namespace std;

class Parcer {
    char *filename;
    int V, E;
    vector<pair<int, int>> edges;

public:
    Parcer(char *filename1) { filename = filename1; }
    void parseFile(const std::string &filename);
    int get_V();
    int get_E();
    vector<pair<int, int>> get_edges();
};


#endif //GREEDYCOLORING_PARCER_H
