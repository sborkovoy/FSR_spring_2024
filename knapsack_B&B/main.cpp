#include <iostream>
#include <vector>
#include "Parcer.h"
#include "Solver.h"

using namespace std;


int main() {
    char filename[20];
    cin >> filename;
    Parser parser(filename);
    parser.parseFile(filename);
    int max_weight = parser.get_max_weight();
    vector<Item> items = parser.get_items();
    int n = items.size();
    Solver solver;

    cout << "Maximum possible profit = " << solver.knapsack(max_weight, items, n);

    return 0;
}