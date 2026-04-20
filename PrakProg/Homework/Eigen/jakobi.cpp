#include "jakobi.h"
#include <iostream>

namespace pp {

Matrix id(int n) {
    Matrix I(n, n);
    for (int i = 0; i < n; ++i) I(i, i) = 1.0;
    return I;
}

bool is_symmetric(const Matrix& A, double tol) {
    if (A.rows() != A.cols()) return false;
    int n = A.rows();
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (std::abs(A(i,j) - A(j,i)) > tol)
                return false;
    return true;
}

double offdiag_norm(const Matrix& A) {
    double s = 0.0;
    for (int i = 0; i < A.rows(); ++i)
        for (int j = 0; j < A.cols(); ++j)
            if (i != j) s += A(i,j)*A(i,j);
    return std::sqrt(s);
}



//rotationerne:
void EVD::timesJ(Matrix& A, int p, int q, double theta) {
    double c = std::cos(theta);
    double s = std::sin(theta);

    for (int i = 0; i < A.rows(); ++i) {
        double aip = A(i,p);
        double aiq = A(i,q);
        A(i,p) = c*aip - s*aiq;
        A(i,q) = s*aip + c*aiq;
    }
}

void EVD::Jtimes(Matrix& A, int p, int q, double theta) {
    double c = std::cos(theta);
    double s = std::sin(theta);

    for (int j = 0; j < A.cols(); ++j) {
        double apj = A(p,j);
        double aqj = A(q,j);
        A(p,j) = c*apj + s*aqj;
        A(q,j) = -s*apj + c*aqj;
    }
}


EVD::EVD(const Matrix& Ain, double tol, int maxSweeps)
    : w(Ain.rows()), V(id(Ain.rows()))
{
    if (Ain.rows() != Ain.cols())
        throw std::invalid_argument("Matrix must be square");

    if (!is_symmetric(Ain, tol))
        throw std::invalid_argument("Matrix must be symmetric");

    Matrix A = Ain;
    int n = A.rows();

    for (int sweep = 0; sweep < maxSweeps; ++sweep) {
        bool changed = false;

        for (int p = 0; p < n - 1; ++p) {
            for (int q = p + 1; q < n; ++q) {

                double apq = A(p,q);
                if (std::abs(apq) < tol) continue;

                double app = A(p,p);
                double aqq = A(q,q);

                double theta = 0.5 * std::atan2(2.0*apq, aqq - app);

                double c = std::cos(theta);
                double s = std::sin(theta);

                double new_app = c*c*app - 2*s*c*apq + s*s*aqq;
                double new_aqq = s*s*app + 2*s*c*apq + c*c*aqq;

                if (std::abs(new_app - app) > tol || std::abs(new_aqq - aqq) > tol) {

                    changed = true;

                    timesJ(A, p, q, theta);   // A ← A J
                    Jtimes(A, p, q, theta);   // A ← Jᵀ A
                    timesJ(V, p, q, theta);   // V ← V J

                    A(p,q) = 0.0;
                    A(q,p) = 0.0;
                }
            }
        }

        if (!changed || offdiag_norm(A) < tol)
            break;
    }

    for (int i = 0; i < n; ++i)
        w[i] = A(i,i);
}
}//namespace pp