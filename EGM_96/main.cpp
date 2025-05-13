#include "Parcer.h"
#include "Solver.h"
#include "Analyser.h"
#include "Presenter.h"
#include "Error.h"


using namespace std;

int main() {
    try {
        char filename[10];
        strcpy(filename, "EGM96.grv");
        Parcer parcer(filename);
        Stocks coeffs[70][71];
        parcer.parce(coeffs);
        Solver solver(70);
        Presenter present;
        int i, j, N = 10;
        double phi, theta;
        double theta_start = -pi / 2;
        double theta_end = pi / 2;
        double phi_start = -pi;
        double phi_end = pi;
        double theta_step = (theta_end - theta_start) / (N - 1);
        double phi_step = (phi_end - phi_start) / (N - 1);
        double **res = new double *[N];
        for (i = 0; i < N; i++) res[i] = new double[N];
        Analyser A;
        int **up;
        int **down;
        int size_up, size_down;
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                phi = phi_start + j * phi_step;
                theta = theta_start + i * theta_step;
                res[i][j] = solver.N(6371000, theta, phi, coeffs);
            }
        }

        A.analys(N, res, 40, -70, up, down, size_up, size_down);
        present.make_file_res(N, res);
        present.make_file_extr(size_up, up, size_down, down);
        for (i = 0; i < size_down; i++) {
            //cout<<res[down[0][i]][down[1][i]]<<endl;
        }
        delete[] up[1];
        delete[] down[1];
        delete[] up[0];
        delete[] down[0];
        delete[] up;
        delete[] down;

        for (i = 0; i < N; i++) delete[] res[i];
        delete[] res;
    }
    catch(Error err){
        err.err_print();
        cout << "Error. See error.txt\n";
    }
    return 0;
}
