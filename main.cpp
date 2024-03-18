#include <algorithm>
#include <random>
#include <stdio.h>
#include <vector>
#include <iostream>
#define EPS 1e-5

using namespace std;

class Point{
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
    double dist(const Point &other){
        return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }
};

class Solver{
public:
    double path_dist(vector<Point> &path);
    void do2opt(vector<Point> &path, int i, int j);
    double optimise_path(vector<Point> path);
    double lengthDelta(vector<Point> &path, int i, int j){
        return path[j].dist(path[i]) - path[i].dist(path[j]);
    }
};

double Solver::optimise_path(vector<Point> path) {
    int n = path.size();
    //double best_dist = path_dist(path);
    bool can_imrove = true;
    int k = 0;
    while((can_imrove) && k < 1000){
        k++;
        //cout << "k = " << k << "   " << can_imrove  << endl;
        can_imrove = false;
        for(int i = 0; i < n - 1; i++){
            for(int j = i + 1; j <= n; j++){
                double lengthDelta = -path[i].dist(path[(i + 1) % n]) - path[j % n].dist(path[(j + 1) % n]) +
                        path[i].dist(path[j % n]) + path[(i + 1) % n].dist(path[(j + 1) % n]);
                //cout << " ---" << lengthDelta << endl;
                if((lengthDelta) < -EPS){
                    //cout << "---" << "We are here!" << endl;
                    do2opt(path, i, j % n);
                    can_imrove = true;
                }
            }
        }
    }
    //cout<<k<<endl;
    return path_dist(path);
}

void Solver::do2opt(vector<Point> &path, int i, int j) {
    swap(*(path.begin() + i + 1), *(path.begin() + j + 1));
}

double Solver::path_dist(vector<Point> &path) {
    double distance = 0;
    for(int i = 0; i < path.size() - 1; i++){
        distance += path[i].dist(path[i + 1]);
    }
    distance += path[path.size() - 1].dist(path[0]);
    return distance;
}

int main(){
    int n;
    cin>>n;
    vector<Point> path(n);
    Solver solver;
    for(int i = 0; i < n; i++)
        cin >> path[i].x >> path[i].y;
    cout << solver.optimise_path(path) << endl;
    for(int i = 0; i < n; i++)
        cout << path[i].x <<" "<< path[i].y<<endl;
    return 0;
}