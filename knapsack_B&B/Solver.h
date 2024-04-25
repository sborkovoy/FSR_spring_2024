//
// Created by sborkovoi on 25.04.2024.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include "Parcer.h"
#include "Item.h"

using namespace std;

#ifndef KNAPSACK_2_SPLIT_SOLVER_H
#define KNAPSACK_2_SPLIT_SOLVER_H


struct Node {
    int level, profit, bound;
    int weight;
};


class Solver {
public:
    int bound(Node u, int n, int W, vector<Item> arr);

    int knapsack(int W, vector<Item> arr, int n);
};

#endif //KNAPSACK_2_SPLIT_SOLVER_H
