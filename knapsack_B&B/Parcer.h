//
// Created by sborkovoi on 25.04.2024.
//
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include "Item.h"

using namespace std;

#ifndef KNAPSACK_2_SPLIT_PARCER_H
#define KNAPSACK_2_SPLIT_PARCER_H

class Parser {
    char *filename;
    int M, max_weight;
    vector<Item> items;

public:
    Parser(char *filename1) { filename = filename1; }
    void parseFile(const std::string &filename);
    vector<Item> get_items();
    int get_number();
    int get_max_weight();
};

#endif //KNAPSACK_2_SPLIT_PARCER_H
