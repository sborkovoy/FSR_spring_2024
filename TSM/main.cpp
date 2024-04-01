
#include "Parcer.h"
#include "Solver.h"


using namespace std;


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
