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


//opgave C
int main(int argc, char** argv) {
    if (argc == 2){
        std::cerr << "Usage: ./main N\n";
    int n = std::atoi(argv[1]);

    Matrix A(n, n);
    std::cout << "n = " << n << "\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            A(i, j) = rnd();

    QR qr(A);
    
    }
    else { 
// opgave A
std::cout << "===== Opgave A: QR test =====\n";

int n1 = 8;
int m1 = 4;

Matrix B(n1, m1);
for (int i = 0; i < n1; i++)
    for (int j = 0; j < m1; j++)
        B(i, j) = rnd();

// Print original matrix
std::cout << "\nMatrix A:\n";
B.print();

// QR factorization
QR qr1(B);
Matrix Q = qr1.getQ();
Matrix R = qr1.getR();

// Print Q og R
std::cout << "\nMatrix Q:\n";
Q.print();

std::cout << "\nMatrix R (should be upper triangular):\n";
R.print();

// --- Check 1: Q^T Q = I ---
std::cout << "\nQ^T * Q (should be identity):\n";
Matrix QT = transpose(Q);
Matrix QTQ = QT * Q;
QTQ.print();

// --- Check 2: Q * R = A ---
std::cout << "\nQ * R (should equal A):\n";
Matrix QR_check = Q * R;
QR_check.print();


// opgave 3: test solve
std::cout << "\n===== Opgave 3: test solve =====\n";

int n2 = 5;
Matrix A2(n2, n2);
for (int i = 0; i < n2; i++)
    for (int j = 0; j < n2; j++)
        A2(i, j) = rnd();

Vector b2(n2);
for (int i = 0; i < n2; i++)
    b2[i] = rnd();

std::cout << "\nMatrix A:\n";
A2.print();

std::cout << "\nVector b:\n";
b2.print_vector();

QR qr2(A2);
Vector x2 = qr2.solve(b2);

std::cout << "\nSolution x from solve(b):\n";
x2.print_vector();

Vector Ax2 = A2 * x2;
std::cout << "\nA*x (should equal b):\n";
Ax2.print_vector();

// opgave B: test inverse
std::cout << "\n===== Opgave B: test inverse =====\n";

int n4 = 5;
Matrix A4(n4, n4);
for (int i = 0; i < n4; i++)
    for (int j = 0; j < n4; j++)
        A4(i, j) = rnd();

std::cout << "\nMatrix A:\n";
A4.print();

QR qr4(A4);
Matrix B4 = qr4.inverse();

std::cout << "\nInverse B = A^{-1}:\n";
B4.print();

Matrix AB4 = A4 * B4;
std::cout << "\nA * B (should be identity):\n";
AB4.print();

// byg identitetsmatrix for sammenligning
Matrix I4(n4, n4);
for (int i = 0; i < n4; i++)
    I4(i, i) = 1.0;

    }
    return 0;
}