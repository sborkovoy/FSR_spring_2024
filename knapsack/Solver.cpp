//
// Created by user on 01.04.2024.
//

#include "Solver.h"
#include "Parcer.h"
#include "Item.h"

using namespace std;

vector<vector<bool>> Solver::generate_population(int population_size, int item_count, vector<Item> items) {
    vector<vector<bool>> population;
    population.resize(population_size);
    for(int i = 0; i<3; i++){
        population[i].resize(item_count);
        for (int j = 0; j < item_count; j++) {
            population[i][j] = 0;
        }
        population[i][rand() % item_count] = 1;
    }

    for (int i = 2; i < population_size; i++) {
        population[i].resize(item_count);
        for (int j = 0; j < item_count; j++) {
            population[i][j] = rand() % 2;
        }
    }
    return population;
}

vector<vector<bool>>
Solver::crossover(vector<vector<bool>> population, vector<Item> items, int item_count, int max_weight) {
    int N = population.size();
    vector<vector<bool>> new_population;

    vector<long int> fit = fitness(population, items, max_weight);
    int index1 = get_fittest(fit);
    int index2 = get_second_fittest(fit, index1);
    new_population.push_back(population[index1]);
    new_population.push_back(population[index2]);

    while (new_population.size() < N) {
        int parent1 = roulette(fit);
        int parent2 = roulette(fit);
        vector<bool> child1(item_count);
        vector<bool> child2(item_count);

        int cross_point = rand() % item_count;
        for (int i = 0; i < item_count; i++) {
            if (i < cross_point) {
                child1[i] = population[parent1][i];
                child2[i] = population[parent2][i];
            } else {
                child1[i] = population[parent2][i];
                child2[i] = population[parent1][i];
            }
        }
        child1 = mutation(child1);
        child2 = mutation(child2);
        new_population.push_back(child1);
        new_population.push_back(child2);
        child1.clear();
        child1.shrink_to_fit();
        child2.clear();
        child2.shrink_to_fit();
    }

    population = new_population;
    new_population.clear();
    new_population.shrink_to_fit();

    return population;
}

vector<long int> Solver::fitness(vector<vector<bool>> population, vector<Item> items, long max_weight) {
    int N = population.size();
    long int sum;
    vector<long int> fitness(N);
    for (int i = 0; i < N; i++) {
        fitness[i] = 0;
    }
    for (int i = 0; i < population.size(); i++) {
        sum = 0;
        for (int j = 0; j < population[i].size(); j++) {
            if (population[i][j] == 1) {
                fitness[i] += items[j].value;
                sum += items[j].weight;
            }
        }
        if (sum > max_weight) {
            fitness[i] = 0;
        }
    }
    return fitness;
}

int Solver::roulette(vector<long> fitness) {
    int max_sum = 0;
    for(int i = 0; i < fitness.size(); i++){
        max_sum += fitness[i];
    }
    int r = rand() % max_sum, sum = 0;
    int index = 0;
    for (int i = 0; i < fitness.size(); i++) {
        sum += fitness[i];
        if (sum > r)
            return i;
    }
    return index;
}

int Solver::get_second_fittest(vector<long> fitness, int max) {
    long int max_second_fitness = INT_MIN, index = -1;
    for (int i = 0; i < fitness.size(); i++) {
        if (i != max && max_second_fitness < fitness[i]) {
            max_second_fitness = fitness[i];
            index = i;
        }
    }
    return index;
}

int Solver::get_fittest(vector<long> fitness) {
    long int max_fitness = INT_MIN, index = -1;
    for (int i = 0; i < fitness.size(); i++) {
        if (max_fitness < fitness[i]) {
            max_fitness = fitness[i];
            index = i;
        }
    }
    return index;
}

vector<bool> Solver::mutation(vector<bool> individual) {
    int N = individual.size();
    for (int i = 0; i < N; i++) {
        if (rand() % 1000 < 1) {
            individual[i] = !individual[i];
        }
    }
    return individual;
}
