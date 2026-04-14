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
    //Init qr på A:
    QR qr(A);

    Matrix Q = qr.getQ();
    Matrix R = qr.getR();

    std::cout << "Q:" << std::endl;
    Q.print();
    std::cout << "R er upper triangular" << std::endl;
    R.print(); 

    std::cout << "QTQ = I:" << std::endl;
    //Traspose af Q
    Matrix QT = transpose(Q);
    Matrix I = QT * Q;

    I.print();

    std::cout << "Q*R = A:" << std::endl;
    Matrix QR1 = Q*R;

    QR1.print();

//Opgave A3)
int n1 = 5, m1 = 5;
Matrix A1(n1, m1);

for (int i = 0; i < n1; i++)
    for (int j = 0; j < m1; j++)
        A1(i, j) = rnd();

A1.print();

// random b
Vector b(n1);
for (int i = 0; i < n1; i++)
    b[i] = rnd();

b.print_vector();

QR qr1(A1);

// solve Ax = b
Vector xsolve = qr1.solve(b);

xsolve.print_vector();

// optional check
Vector check = A1 * xsolve;
check.print_vector();


//Determinanten:

std::cout << "Determinanten:" << std::endl;
Matrix R1 = qr1.getR();
R1.print();
double determinant = qr1.det();
std::cout << determinant << std::endl;



    return 0;
}