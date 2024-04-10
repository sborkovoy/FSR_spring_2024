#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;


#include "Parcer.h"

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
