#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <cstdlib>
#define a 6378136.3
#define mu 3.986004415e14
#define pi 3.1415926535

#define eps 1e-3


class Presenter{
public:
    void make_file_res(int N, double **res);
    void make_file_extr(int size_up, int** up, int size_down, int **down);
};
