#pragma once
#include "matrix.h"

namespace la {

struct QR {
    Matrix Q; // n×m
    Matrix R; // m×m

    explicit QR(const Matrix& A);

    
    Vector solve(const Vector& b) const;

    Matrix inverse() const; 

    double det() const;

    //getter metoder:
    const Matrix& getQ() const;
    const Matrix& getR() const;
};

}