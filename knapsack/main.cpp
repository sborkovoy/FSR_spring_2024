#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

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

void Parcer::parceFile(const string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }
    file >> M >> max_weight;
    for (int i = 0; i < M; i++) {
        Item item;
        file >> item.value >> item.weight;
        items.push_back(item);
    }
    file.close();
}

class Solver {

public:
    vector<vector<bool>> generate_population(int population_size, int item_count,
                                             vector<Item> items) {
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

    vector<long int> fitness(vector<vector<bool>> population, vector<Item> items,
                             long int max_weight) {
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

    int get_fittest(vector<long int> fitness) {
        long int max_fitness = INT_MIN, index = -1;
        for (int i = 0; i < fitness.size(); i++) {
            if (max_fitness < fitness[i]) {
                max_fitness = fitness[i];
                index = i;
            }
        }
        return index;
    }

    int get_second_fittest(vector<long int> fitness, int max) {
        long int max_second_fitness = INT_MIN, index = -1;
        for (int i = 0; i < fitness.size(); i++) {
            if (i != max && max_second_fitness < fitness[i]) {
                max_second_fitness = fitness[i];
                index = i;
            }
        }
        return index;
    }

    vector<bool> mutation(vector<bool> individual) {
        int N = individual.size();
        for (int i = 0; i < N; i++) {
            if (rand() % 1000 < 1) {
                individual[i] = !individual[i];
            }
        }
        return individual;
    }

    int roulette(vector<long int> fitness) {
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

    vector<vector<bool>> crossover(vector<vector<bool>> population,
                                   vector<Item> items, int item_count,
                                   int max_weight) {
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
};

int main() {
    srand(time(NULL));
    /*int M, max_weight;
    cin >> M >> max_weight;
    vector<Item> items(M);
    for (int i = 0; i < M; i++) {
      cin >> items[i].value >> items[i].weight;
    }*/
    char filename[20];
    cin >> filename;
    Parcer parcer(filename);
    parcer.parceFile(filename);
    int M = parcer.get_number();
    int max_weight = parcer.get_max_weight();
    vector<Item> items = parcer.get_items();
    Solver solver;
    vector<vector<bool>> gen1 = solver.generate_population(2*M, M, items);
    vector<long int> fit_first;



    bool flag = 1;
    for (int i = 0; i < 100 && (flag); i++) {
        //cout << i << endl;
        gen1 = solver.crossover(gen1, items, M, max_weight);
        vector<long int> fit = solver.fitness(gen1, items, max_weight);
        int index1 = solver.get_fittest(fit);
        int index2 = solver.get_second_fittest(fit, fit[index1]);
        //if(fit[index2] / fit[index1] > 0.999) flag = 0;
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
