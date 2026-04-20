#include "jakobi.h"
#include <iostream>
#include <random>
#include <cmath>
#include <exception>

using namespace pp;

Matrix diag(const Vector& w) {
    Matrix D(w.size(), w.size());
    for (int i = 0; i < w.size(); ++i) D(i,i) = w[i];
    return D;
}

double norm_diff(const Matrix& A, const Matrix& B) {
    if (A.rows() != B.rows() || A.cols() != B.cols())
        throw std::invalid_argument("norm_diff: dimension mismatch");

    double s = 0.0;
    for (int i = 0; i < A.rows(); ++i) {
        for (int j = 0; j < A.cols(); ++j) {
            double d = A(i,j) - B(i,j);
            s += d*d;
        }
    }
    return std::sqrt(s);
}

Matrix identity(int n) {
    Matrix I(n,n);
    for (int i = 0; i < n; ++i) I(i,i) = 1.0;
    return I;
}

Matrix random_symmetric_matrix(int n) {
    Matrix A(n,n);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-5.0, 5.0);

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            double x = dist(gen);
            A(i,j) = x;
            A(j,i) = x;
        }
    }

    return A;
}

int main() {
    try {
        int n = 4;

        Matrix A = random_symmetric_matrix(n);

        std::cout << "A:\n";
        A.print();

        EVD evd(A);

        Matrix D  = diag(evd.w);
        Matrix VT = transpose(evd.V);
        Matrix I  = identity(n);

        Matrix VTAV = VT * A * evd.V;
        Matrix VDVt = evd.V * D * VT;
        Matrix VTV  = VT * evd.V;
        Matrix VVT  = evd.V * VT;

        std::cout << "\nEigenvalues:\n";
        evd.w.print_vector();

        std::cout << "\nV:\n";
        evd.V.print();

        std::cout << "\nD:\n";
        D.print();

        std::cout << "\nV^T A V:\n";
        VTAV.print();

        std::cout << "\nV D V^T:\n";
        VDVt.print();

        std::cout << "\nV^T V:\n";
        VTV.print();

        std::cout << "\nV V^T:\n";
        VVT.print();

        std::cout << "\nFejlmaal:\n";
        std::cout << "||V^T A V - D|| = " << norm_diff(VTAV, D) << "\n";
        std::cout << "||V D V^T - A|| = " << norm_diff(VDVt, A) << "\n";
        std::cout << "||V^T V - I||   = " << norm_diff(VTV, I) << "\n";
        std::cout << "||V V^T - I||   = " << norm_diff(VVT, I) << "\n";

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Fejl: " << e.what() << "\n";
        return 1;
    }
}