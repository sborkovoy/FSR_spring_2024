//
// Created by user on 25.12.2023.
//

#include "Solver.h"
#include "Error.h"




long double Solver::U(double r, double theta, double phi, Stocks (*coeffs)[71]) {
    double res = 0.0;
    int n, m;
    double tmp;
    for(n = 2; n < MAX+1; n++){
        tmp = 0.0;
        for(m = 1; m < n+1; m++){
            tmp = tmp + norm(assoc_legendre(n, m, sin(theta)), n, m) * (coeffs[n-1][m].C*cos(m*phi) + coeffs[n-1][m].S*sin(m*phi));
        }
        res = res + tmp*pow(double(a)/r, n) + pow(double(a)/r, n)*norm(assoc_legendre(n, 0, sin(theta)), n, 0)*coeffs[n-1][0].C;
    }
    if (abs(r) < eps){
        cout<<Error::SOLVE<<endl;
        throw Error(Error::SOLVE);
        return 0;
    }
    res = -(mu/r) * (1.0 + res);
    return res;
}

long double Solver::V(double r, double theta, double phi, Stocks (*coeffs)[71]) {
    double res = 0;
    int n;
    for(n = 2; n < MAX+1; n = n + 2){
        res = res + pow((double)(a)/r, n)*norm(assoc_legendre(n, 0, sin(theta)), n, 0)*coeffs[n-1][0].C;
    }
    if (abs(r) < eps){
        cout<<Error::SOLVE<<endl;
        throw Error(Error::SOLVE);
        return 0;
    }
    res = -(mu/r) * (1.0 + res);
    return res;
}

long double Solver::N(double r, double theta, double phi, Stocks (*coeffs)[71]) {
    double N = U(r, theta, phi, coeffs) - V(r, theta, phi, coeffs);

    N = -N*pow(a, 2)/mu;
    if (abs(mu) < eps){
        throw Error(Error::SOLVE);
        return 0;
    }

    return N;
}

long double Solver::factorial(int n) {
    long double res = 1;
    for(int i=1; i<=n; ++i){
        res = res * i;
    }
    return res;
}

long double Solver::norm(long double x, int n, int m) {
    int i;
    x = x * sqrt ((double) (2 - (m==0)) * (2*n + 1) * factorial(n-m) / factorial(n+m));
    return x;
}

Solver::Solver(int max) : MAX(max) {}

