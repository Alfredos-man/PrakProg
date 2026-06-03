
#include "newton.h"
#include "QR.h"
#include <stdexcept>

namespace la {

NewtonResult newton(
    std::function<Vector(const Vector&)> f,
    std::function<Matrix(const Vector&)> J,
    Vector x,
    double tol,
    int max_iter
) {
    for (int k = 0; k < max_iter; ++k) {
        Vector fx = f(x);

        if (fx.norm() < tol) {
            return {x, k, true};
        }

        Matrix Jx = J(x);

        // Newton step: J(x) * dx = -f(x)
        Vector rhs = fx * (-1.0);

        QR qr(Jx);
        Vector dx = qr.solve(rhs);

        x += dx;

        if (dx.norm() < tol) {
            return {x, k + 1, true};
        }
    }

    return {x, max_iter, false}; //max_iter og den sidste bool kan undlades 
}

}