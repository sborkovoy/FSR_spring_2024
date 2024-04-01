//
// Created by user on 22.03.2024.
//

#include "Solver.h"
using namespace std;
#include "Parcer.h"

double Solver::optimise_path(vector<Point> path) {
    vector<int> path_index(path.size());
    for (int i = 0; i < path.size(); i++)
        path_index[i] = i;
    int n = path.size();
    bool can_imrove = true;
    int k = 0;
    double before_swap;
    while ((can_imrove)) {
        k++;
        can_imrove = false;
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                before_swap = path_dist(path);
                if ((lengthDelta(path[i], path[(i + 1)], path[j], path[(j + 1) % n])) <
                    -EPS) {
                    reverse(begin(path) + i + 1, begin(path) + j + 1);
                    swap(path_index[(i + 1)], path_index[(j + 1) % n]);
                    cout << path_dist(path) << endl;
                    can_imrove = true;
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
        cout << path_index[i] << " ";
    cout << path_index[0];
    cout << endl;
    return path_dist(path);
}

void Solver::do2opt(vector<Point> &path, int i, int j) {
    swap(*(path.begin() + i + 1), *(path.begin() + j + 1));
}

double Solver::path_dist(vector<Point> &path) {
    double distance = 0;
    for (int i = 0; i < path.size() - 1; i++) {
        distance += dist(path[i], path[i + 1]);
    }
    distance += dist(path[path.size() - 1], path[0]);
    return distance;
}