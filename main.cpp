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
};

class Solver{
public:
    double path_dist(vector<Point> &path);
    void do2opt(vector<Point> &path, int i, int j);
    double optimise_path(vector<Point> path);
    double dist(Point p1, Point p2){
        return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
    }
    double lengthDelta(Point a1, Point a2, Point b1, Point b2){
        return -dist(a1, a2)-dist(b1, b2)+dist(a1, b1)+dist(a2, b2);
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
                //cout << " ---" << lengthDelta(path[i], path[i+1], path[j], path[(j+1) % n]) << endl;
                //cout<<i<<" "<<j<<" "<<endl;
                if((lengthDelta(path[i], path[i+1], path[j], path[j+1])) < -EPS){
                    //cout << "---" << "We are here!" << endl;
                    swap(path[(i+1) % n], path[(j+1) % n]);
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
        distance += dist(path[i], path[i + 1]);
    }
    distance += dist(path[path.size() - 1], path[0]);
    return distance;
}

int main(){
    int n;
    cin>>n;
    vector<Point> path(n);
    Solver solver;
    for(int i = 0; i < n; i++)
        cin >> path[i].x >> path[i].y;
    cout << solver.path_dist(path)<<endl;
    cout << solver.optimise_path(path) << endl;
    return 0;
}

