#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <stdio.h>
#include <string.h>
#include <vector>
#define EPS 1e-5

using namespace std;

class Point {
public:
    double x, y;
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
    Point() {
        this->x = 0;
        this->y = 0;
    }
};

class Parcer {
    char *filename;

public:
    Parcer(char *filename1) { filename = filename1; }
    vector<Point> parce();
};

vector<Point> Parcer::parce() {
    double x, y;
    std::ifstream F(filename);
    vector<Point> path(0);
    if (F.is_open() == 0) {
        cout << "cannot read file!" << endl;
        return path;
    }
    int n;
    F >> n;
    // char s[100];
    for (int i = 0; i < n; i++) {
        F >> x >> y;
        path.push_back(Point(x, y));
    }
    F.close();
    return path;
}

class Solver {
public:
    double path_dist(vector<Point> &path);
    void do2opt(vector<Point> &path, int i, int j);
    double optimise_path(vector<Point> path);
    double dist(Point p1, Point p2) {
        return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }
    double lengthDelta(Point a1, Point a2, Point b1, Point b2) {
        return -dist(a1, a2) - dist(b1, b2) + dist(a1, b1) + dist(a2, b2);
    }
};

double Solver::optimise_path(vector<Point> path) {
    vector<int> path_index(path.size());
    for (int i = 0; i < path.size(); i++)
        path_index[i] = i;
    int n = path.size();
    bool can_imrove = true;
    int k = 0;
    while ((can_imrove) && k < 1000) {
        k++;
        can_imrove = false;
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j <= n; j++) {
                if ((lengthDelta(path[i], path[i + 1], path[j], path[(j + 1) % n])) <
                    -EPS) {
                    swap(path[(i + 1) % n], path[(j + 1) % n]);
                    swap(path_index[i + 1], path_index[j + 1]);
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

int main() {
    char filename[10];
    cin >> filename;
    // strcpy(filename, "tsp_51_1");
    Parcer parcer(filename);
    vector<Point> path = parcer.parce();
    Solver solver;
    cout << solver.optimise_path(path) << endl;
    return 0;
}
