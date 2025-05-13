#include "Parcer.h"
#include "Error.h"
using namespace std;

void Parcer::parce(Stocks (*coeffs)[71]) {

    int k, i, j;
    int cnt=0;

    FILE* F = fopen(filename, "r");
    if (F == 0){
        cout<<Error::FILE_read<<endl;
        throw Error(Error::FILE_read);
        return;
    }
    char s[100];
    while(fscanf(F, "%s", s) && strcmp(s, "Coefficients") != 0  );

    for(i = 0; i<70; i++)
        for(j = 0; j<71; j++) {
            coeffs[i][j].C = 0;
            coeffs[i][j].S = 0;
        }

    while( fscanf(F, "%s", s) && strcmp(s, "END") != 0  ){
        cnt++;
    }
    fclose( F );
    if(!cnt){
        cout<<Error::FILE_coefs<<endl;
        throw Error(Error::FILE_coefs);
        return;
    }

    F = fopen( filename, "r" );
    if (F == 0){
        cout<<Error::FILE_read<<endl;
        throw Error(Error::FILE_read);
        return;
    }

    while(fscanf(F, "%s", s) && strcmp(s, "Coefficients") != 0  );
    for( k = 0; k < cnt/4 ; k++ ){
        fscanf(F, "%d %d", &i, &j );
        if(i>70 || i<0 || j>71 || j<0){
            fclose(F);
            throw Error(Error::FILE_data);
            return;
        }
        fscanf(F, "%lf %lf", &(coeffs[i-1][j].C), &(coeffs[i-1][j].S) );
    }
    fclose(F);
    return;
}
