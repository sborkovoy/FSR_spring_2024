#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <cstdlib>
#include "Parcer.h"

#define a 6378136.3
#define mu 3.986004415e14
#define pi 3.1415926535

#define eps 1e-3

using namespace std;



#ifndef SOLVER_H
#define SOLVER_H
class Solver{
    long double factorial(int n);
    long double norm(long double x, int n, int m);
public:
    int MAX;

    explicit Solver(int max=20);

    long double U(double r, double theta, double phi, Stocks coeffs[70][71]);

    long double V(double r, double theta, double phi, Stocks coeffs[70][71]);

    long double N(double r, double theta, double phi, Stocks coeffs[70][71]);



};

#endif
