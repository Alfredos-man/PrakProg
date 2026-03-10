#pragma once
#include "matrix.h"

namespace la {

struct QR {
    Matrix Q; // n×m
    Matrix R; // m×m

    explicit QR(const Matrix& A);

    
    Vector solve(const Vector& b) const;

    double det() const;
};

}