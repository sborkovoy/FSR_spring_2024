#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include "Parcer.h"
#include "Solver.h"
#include "Item.h"

using namespace std;

int main() {
    srand(time(NULL));
    char filename[20];
    cin >> filename;
    Parcer parcer(filename);
    parcer.parceFile(filename);
    int M = parcer.get_number();
    int max_weight = parcer.get_max_weight();
    vector<Item> items = parcer.get_items();
    Solver solver;
    vector<vector<bool>> gen1 = solver.generate_population(2*M, M, items);
    for (int i = 0; i < 100; i++) {
        gen1 = solver.crossover(gen1, items, M, max_weight);
        vector<long int> fit = solver.fitness(gen1, items, max_weight);
    }
    vector<long int> fit = solver.fitness(gen1, items, max_weight);
    int best_index = solver.get_fittest(fit);
    int final_value = 0, final_weight = 0;
    for (int i = 0; i < M; i++) {
        final_value += items[i].value * gen1[best_index][i];
        final_weight += items[i].weight * gen1[best_index][i];
    }
    cout << final_value << " " << max_weight - final_weight << endl;
    for (int i = 0; i < M; i++) {
        cout << gen1[best_index][i] << " ";
    }
    return 0;
}