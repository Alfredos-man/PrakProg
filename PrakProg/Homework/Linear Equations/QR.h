#pragma once
#include "matrix.h"

namespace la {

// QR factorization of A (n×m, n>=m) using modified Gram–Schmidt.
// Produces Q (n×m) with orthonormal columns and R (m×m) upper triangular such that A = Q R.
struct QR {
    Matrix Q; // n×m
    Matrix R; // m×m

    explicit QR(const Matrix& A);

    // Solve A x = b using QR (least squares if A is tall).
    Vector solve(const Vector& b) const;

    // det(A) for square A (n==m). Equals product diag(R).
    double det() const;
};

} // namespace la