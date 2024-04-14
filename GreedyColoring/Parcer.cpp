

#include "Parcer.h"
#include "Graph.h"

using namespace std;

void Parcer::parseFile(const string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }
    file >>V>>E;
    int w, v;
    for (int i = 0; i < E; i++) {
        file >> v >> w;
        edges.push_back({v, w});
    }
    file.close();
}

int Parcer::get_V() { return V; }

int Parcer::get_E() { return E; }

vector<pair<int, int>> Parcer::get_edges() { return edges; }
