//
// Created by sborkovoi on 25.04.2024.
//

#include "Parcer.h"


void Parser::parseFile(const string &filename) {
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

vector<Item> Parser::get_items() { return items; }

int Parser::get_number() { return M; }

int Parser::get_max_weight() { return max_weight; }
