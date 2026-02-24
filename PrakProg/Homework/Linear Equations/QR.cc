#include "QR.h"
#include <cmath>
#include <stdexcept>

namespace la {

QR::QR(const Matrix& A) {
    int n = A.rows();
    int m = A.cols();
    if (n < m) throw std::invalid_argument("QR: require n >= m");

    Q = Matrix(n, m);
    R = Matrix(m, m);

    // Copy A into Q (we will overwrite columns)
    for (int j = 0; j < m; ++j) Q.set_col(j, A.col(j));

    // Modified Gram–Schmidt
    for (int i = 0; i < m; ++i) {
        Vector qi = Q.col(i);
        double rii = qi.norm();
        if (rii < 1e-14) throw std::runtime_error("QR: rank deficient / dependent columns");
        R(i, i) = rii;
        qi /= rii;
        Q.set_col(i, qi);

        for (int j = i + 1; j < m; ++j) {
            Vector qj = Q.col(j);
            double rij = dot(qi, qj);
            R(i, j) = rij;
            qj -= qi * rij;
            Q.set_col(j, qj);
        }
    }

    // Explicitly zero below diagonal
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < i; ++j)
            R(i, j) = 0.0;
}

Vector QR::solve(const Vector& b) const {
    if (b.size() != Q.rows()) throw std::invalid_argument("QR::solve: b size mismatch");

    int n = Q.rows();
    int m = Q.cols();

    // y = Q^T b
    Vector y(m);
    for (int i = 0; i < m; ++i) {
        double s = 0.0;
        for (int k = 0; k < n; ++k) s += Q(k, i) * b[k];
        y[i] = s;
    }

    // Back substitution: R x = y
    Vector x(m);
    for (int i = m - 1; i >= 0; --i) {
        double s = y[i];
        for (int k = i + 1; k < m; ++k) s -= R(i, k) * x[k];
        double rii = R(i, i);
        if (std::abs(rii) < 1e-14) throw std::runtime_error("QR::solve: singular R");
        x[i] = s / rii;
    }
    return x;
}

double QR::det() const {
    if (Q.rows() != Q.cols()) throw std::invalid_argument("QR::det: only for square A (n==m)");
    int m = R.rows();
    double d = 1.0;
    for (int i = 0; i < m; ++i) d *= R(i, i);
    return d;
}

} // namespace la