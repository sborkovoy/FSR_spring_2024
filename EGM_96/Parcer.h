#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>

using namespace std;

#ifndef STOCKS_H
#define STOCKS_H
typedef struct Stocks{
    double C;
    double S;
}Stocks;
#endif


#ifndef PARCER_H
#define PARCER_H
class Parcer{
    char* filename;
public:
    Parcer(char* filename1){
        filename = filename1;
    }
    void parce(Stocks (*coeffs)[71]);
};
#endif