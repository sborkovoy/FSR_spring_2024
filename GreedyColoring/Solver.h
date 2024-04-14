
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <fstream>
#include "Graph.h"

using namespace std;

#ifndef GREEDYCOLORING_SOLVER_H
#define GREEDYCOLORING_SOLVER_H

class Solver {
public:
    void GreedyColoring(int V, Graph &g);
};




#endif //GREEDYCOLORING_SOLVER_H
