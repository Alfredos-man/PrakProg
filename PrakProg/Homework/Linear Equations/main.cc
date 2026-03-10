#include <iostream>
#include <random>
#include <cmath>
#include "QR.h"

using namespace la;


//helper funktioner:

static double rnd() {
    static std::mt19937 gen(123);
    static std::uniform_int_distribution<int> dist(-2, 5);
    return dist(gen);
}

static bool approx(double x, double y, double tol = 1e-10) {
    return std::abs(x - y) <= tol;
}

int main() {
   
    /*
    generate a random tall (n>m) matrix A (of a modest size);
    factorize it into QR;
    check that R is upper triangular;
    check that QTQ=1;
    check that QR=A;
    */

    //test en høj matrix med n>m

    
    int n=8,m=3;
    Matrix A(n,m);
    for(int i = 0; i<n; i++)
        for (int j = 0; j < m; j++)
            A(i,j) = rnd();

    //printer matrix
    A.print();

    //tjek de forskellige ting
    QR qr(A);

    
    
    


    return 0;
}