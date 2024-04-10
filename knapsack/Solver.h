//
// Created by user on 01.04.2024.
//

#ifndef KNAPSACK_SPLIT_SOLVER_H
#define KNAPSACK_SPLIT_SOLVER_H

#include "Parcer.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <utility>

using namespace std;

class Solver {
public:
    vector<vector<bool>> generate_population(int population_size, int item_count,
                                             vector<Item> items);

    vector<long int> fitness(vector<vector<bool>> population, vector<Item> items,
                             long int max_weight);

    int get_fittest(vector<long int> fitness);

    int get_second_fittest(vector<long int> fitness, int max);

    static vector<bool> mutation(vector<bool> individual);

    int roulette(vector<long int> fitness);

    vector<vector<bool>> crossover(vector<vector<bool>> population,
                                   vector<Item> items, int item_count,
                                   int max_weight);
};



#endif //KNAPSACK_SPLIT_SOLVER_H
