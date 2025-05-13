#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <cstdlib>
//#include "Parcer.h"
#define a 6378136.3
#define mu 3.986004415e14
#define pi 3.1415926535

#define eps 1e-3

class Analyser{
    int* search_next(int N, double **mat, int **col);
    int** find(int N, double **mat, int type, int &size);
public:
    Analyser(){}
    ~Analyser(){}
    void analys(int N, double **mat, double up, double down, int** &peak,  int** &bottom, int &size_up, int &size_bottom);
};

