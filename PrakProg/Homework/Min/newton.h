
#pragma once
#include "matrix.h"
#include <functional>

namespace la {
//fra roots:
struct NewtonResult {
    Vector x;
    int iterations;
    bool converged;
};

NewtonResult newton(
    std::function<Vector(const Vector&)> f,
    std::function<Matrix(const Vector&)> J,
    Vector x,
    double tol = 1e-10,
    int max_iter = 100
);

 //min opgave
NewtonResult newton(
    std::function<double(const Vector&)> phi,
    Vector x0,
    double acc = 1e-3,
    int max_iter = 1000
);

Vector gradient(
    std::function<double(const Vector&)> phi,
    const Vector& x
);

Matrix hessian(
    std::function<double(const Vector&)> phi,
    const Vector& x
);

}