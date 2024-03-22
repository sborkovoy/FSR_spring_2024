//
// Created by user on 22.03.2024.
//
#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
#include "Parcer.h"
#ifndef OPT2_SPLIT_SOLVER_H
#define OPT2_SPLIT_SOLVER_H
#define EPS 1e-5
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
#endif //OPT2_SPLIT_SOLVER_H
