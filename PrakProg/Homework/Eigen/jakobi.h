#pragma once
#include "matrix.h"
#include <tuple>
#include <cmath>
#include <stdexcept>

namespace pp {

struct EVD {
    Vector w;   // eigenvalues
    Matrix V;   // eigenvectors as columns

    EVD(const Matrix& A, double tol = 1e-12, int maxSweeps = 100);

    static void timesJ(Matrix& A, int p, int q, double theta);
    static void Jtimes(Matrix& A, int p, int q, double theta);
};

std::tuple<Vector, Matrix> jacobi(const Matrix& A, double tol = 1e-12, int maxSweeps = 100);

Matrix id(int n);
double offdiag_norm(const Matrix& A);
bool is_symmetric(const Matrix& A, double tol = 1e-12);

} // namespace pp