//
// Created by user on 22.03.2024.
//

#include "Parcer.h"


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