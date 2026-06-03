
#pragma once
#include "matrix.h"
#include <functional>

namespace la {

struct NewtonResult {
    Vector x;
    int iterations;
    bool converged;
};

NewtonResult newton(
    std::function<Vector(const Vector&)> f,
    std::function<Matrix(const Vector&)> J,
    Vector x0,
    double tol = 1e-10,
    int max_iter = 100
);

}