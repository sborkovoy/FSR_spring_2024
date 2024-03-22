#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
#ifndef OPT2_SPLIT_PARCER_H
#define OPT2_SPLIT_PARCER_H

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

#endif //OPT2_SPLIT_PARCER_H
