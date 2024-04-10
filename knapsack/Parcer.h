//
// Created by user on 01.04.2024.
//

#ifndef KNAPSACK_SPLIT_PARCER_H
#define KNAPSACK_SPLIT_PARCER_H
#include <vector>
#include <fstream>
#include <iostream>
#include <utility>

using namespace std;

struct Item {
    long int value, weight;
};

class Parcer {
    char *filename;
    long int max_weight, M;
    vector<Item> items;

public:
    Parcer(char *filename1) { filename = filename1; }
    void parceFile(const std::string &filename);
    vector<Item> get_items() { return items; }
    long int get_number() { return M; }
    long int get_max_weight() { return max_weight; }
};


#endif //KNAPSACK_SPLIT_SOLVER_H

