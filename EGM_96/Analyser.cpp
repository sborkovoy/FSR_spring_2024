//
// Created by user on 25.12.2023.
//

#include "Analyser.h"
#include <iostream>
#include "Error.h"


void Analyser::analys(int N, double **mat, double up, double down, int **&peak, int **&bottom, int &size_up,
                      int &size_bottom) {


    int i, j;

    double ** mat_up = new double* [N];
    double ** mat_down = new double* [N];

    if (mat_up == 0 || mat_down == 0){
        if(mat_down) delete[] mat_down;
        if(mat_up) delete[] mat_up;

        throw Error(Error::DATA);
        return;
    }




    for(i = 0; i < N; i++){
        mat_up[i] = new double [N];
        mat_down[i] = new double [N];
        if (mat_up[i] == 0 || mat_down[i] == 0){

            for(int j=0; j<i-1; j++){
                delete[] mat_up[j];
                delete[] mat_down[j];
            }
            if(mat_up[i]) delete[] mat_up[i];
            if(mat_down[i]) delete[] mat_down[i];

            throw Error(Error::DATA);
            return;
        }
    }




    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++){
            mat_up[i][j] = 0;
            mat_up[i][j] = 0;
        }

    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            if(mat[i][j] > up) mat_up[i][j] = mat[i][j];

    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++) if(mat[i][j] < down) mat_down[i][j] = mat[i][j];

    bottom = find(N , mat_down, -1, size_bottom);
    peak = find(N , mat_up, 1, size_up);

    for(i = 0; i<N; i++) delete[] mat_down[i];
    delete[] mat_down;

    for(i = 0; i<N; i++) delete[] mat_up[i];
    delete[] mat_up;
}

int *Analyser::search_next(int N, double **mat, int **col) {
    int* ans = new int [2];
    if( ans == 0 ){
        throw Error(Error::DATA);
        return 0;
    }
    ans[0] = -1;
    ans[1] = -1;

    int i, j;
    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            if(abs(mat[i][j]) > eps && col[i][j] == 0){
                ans[0] = i;
                ans[1] = j;
                return ans;
            }

    return ans;
}

int **Analyser::find(int N, double **mat, int type, int &size) {
    int i, j;
    int **col = new int* [N];
    if( col == 0 ){
        throw Error(Error::DATA);
        return 0;
    }
    for(i = 0; i < N; i++) {
        col[i] = new int [N];
        if( col[i] == 0 ){
            for(j=0; j < i-1; j++){
                delete[] col[j];
            }
            delete[] col;
            throw Error(Error::DATA);
            return 0;

        }
    }

    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++) col[i][j] = 0;
    std::queue <int*> q;
    int* start;
    double max;
    int* max_ind, *v;
    int* tmp = new int[2];
    int** ans = new int* [2];
    if (tmp == 0){

        for(i=0; i < N; i++){
            for(j=0; j < N; j++){
                delete[] col[j];
            }

            delete[] col;
        }
        throw Error(Error::DATA);
        return 0;
    }
    if (ans == 0){

        for(j=0; j < N; j++){
            delete[] col[j];
        }

        delete[] col;
        throw Error(Error::DATA);
        return 0;
    }

    ans[0] = 0;
    ans[1] = 0;

    size = 0;
    while ((start = search_next(N, mat, col))[0] != -1){
        max = mat[start[0]][start[1]] * type;
        max_ind = start;
        q.push(start);

        while(!q.empty()){
            v = q.front();
            col[v[0]][v[1]] = 1;
            if(max < mat[v[0]][v[1]] * type){
                max = mat[v[0]][v[1]] * type;
                max_ind[0] = v[0];
                max_ind[1] = v[1];
            }
            if(v[0] + 1 < N && col[v[0] + 1][v[1]] == 0 && abs(mat[v[0] + 1][v[1]]) > eps){
                col[v[0] + 1][v[1]] = -1;
                tmp = new int[2];
                tmp[0] = v[0] + 1;
                tmp[1] = v[1];
                q.push(tmp);
            }
            if(v[1] + 1 < N && col[v[0]][v[1] + 1] == 0 && abs(mat[v[0]][v[1] + 1]) > eps){
                col[v[0]][v[1] + 1] = -1;
                tmp = new int[2];
                tmp[0] = v[0];
                tmp[1] = v[1] + 1;
                q.push(tmp);
            }
            if(v[0] - 1 >= 0  && col[v[0] - 1][v[1]] == 0 && abs(mat[v[0] - 1][v[1]]) > eps){
                col[v[0] - 1][v[1]] = -1;
                tmp = new int[2];
                tmp[0] = v[0] - 1;
                tmp[1] = v[1];
                q.push(tmp);
            }
            if(v[1] - 1 >= 0  && col[v[0]][v[1] - 1] == 0 && abs(mat[v[0]][v[1] - 1]) > eps){
                col[v[0]][v[1] - 1] = -1;
                tmp = new int[2];
                tmp[0] = v[0];
                tmp[1] = v[1] - 1;
                q.push(tmp);
            }
            if(v[0] + 1 < N && v[1] + 1 < N  && col[v[0] + 1][v[1] + 1] == 0 && abs(mat[v[0] + 1][v[1] + 1]) > eps){
                col[v[0] + 1][v[1] + 1] = -1;
                tmp = new int[2];
                tmp[0] = v[0] + 1;
                tmp[1] = v[1] + 1;
                q.push(tmp);
            }
            if(v[0] + 1 < N && v[1] - 1 >= 0  && col[v[0] + 1][v[1] - 1] == 0 && abs(mat[v[0] + 1][v[1] - 1]) > eps){
                col[v[0] + 1][v[1] - 1] = -1;
                tmp = new int[2];
                tmp[0] = v[0] + 1;
                tmp[1] = v[1] - 1;
                q.push(tmp);
            }
            if(v[0] - 1 >= 0 && v[1] + 1 < N  && col[v[0] - 1][v[1] + 1] == 0 && abs(mat[v[0] - 1][v[1] + 1]) > eps){
                col[v[0] - 1][v[1] + 1] = -1;
                tmp = new int[2];
                tmp[0] = v[0] - 1;
                tmp[1] = v[1] + 1;
                q.push(tmp);
            }
            if(v[0] - 1 >= 0 && v[1] - 1 >= 0  && col[v[0] - 1][v[1] - 1] == 0 && abs(mat[v[0] - 1][v[1] - 1]) > eps){
                col[v[0] - 1][v[1] - 1] = -1;
                tmp = new int[2];
                tmp[0] = v[0] - 1;
                tmp[1] = v[1] - 1;
                q.push(tmp);
            }
            q.pop();

            //delete[] v;
        }

        ans[0] = (int*)realloc(ans[0], (++size)*sizeof(int));
        ans[1] = (int*)realloc(ans[1], size*sizeof(int));

        if (ans[1] == 0 || ans[0] == 0){

            for(j=0; j<N; j++){
                    delete[] col[j];
            }
            delete[] col;
            if(ans[0]) delete[] ans[0];
            if(ans[1]) delete[] ans[1];


            throw Error(Error::DATA);
            return 0;
        }

        ans[0][size-1] = max_ind[0];
        ans[1][size-1] = max_ind[1];
    }
    for(i = 0; i<N; i++) delete[] col[i];
    delete[] col;
    return ans;
}