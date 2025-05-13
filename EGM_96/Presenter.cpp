#include "Presenter.h"
#include "Error.h"

#include <cstring>


void Presenter::make_file_res(int N, double **res) {
    int i, j;
    FILE* file = fopen("result.txt", "w");
    if (file == 0){
        throw Error(Error::FILE_read);
        return;
    }
    fprintf(file, "%d\n", N);
    for(i=0; i<N; i++) {
        for (j = 0; j < N; j++) {
            fprintf(file, "%e ", res[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void Presenter::make_file_extr(int size_up, int** up, int size_down, int **down){
    int i;
    FILE* file = fopen("extr.txt", "w");
    if (file == 0){
        throw Error(Error::FILE_read);
        return;
    }
    fprintf(file, "%d\n",  size_up);
    for(i = 0; i < size_up; i++){
        fprintf(file, "%d %d\n",  up[0][i], up[1][i]);
    }
    fprintf(file, "%d\n",  size_down);
    for(i = 0; i < size_down; i++){
        fprintf(file, "%d %d\n",  down[0][i], down[1][i]);
    }
    fclose(file);


}
