//
// Created by user on 25.12.2023.
//
#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>

using namespace std;

class Error{
    string type = "error.txt";
public:
    string str;
    enum error{FILE_read, FILE_coefs, FILE_data, DATA, SOLVE};
    Error(error exceptions){
        switch(exceptions){
            case FILE_read:
                str = "Can not read file\n";
                break;
            case FILE_coefs:
                str = "Can not read coefs\n";
                break;
            case FILE_data:
                str = "Wrong degree or order\n";
                break;
            case DATA:
                str = "Can not allocate array\n";
                break;
            case SOLVE:
                str = "Division by zero\n";
                break;
        }
    }
    void err_print(){
        ofstream out(type);
        out << str;
    }
};