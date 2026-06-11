
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


Matrix hessian(
    std::function<double(const Vector&)> phi,
    const Vector& x
) {
    int n = x.size();
    Matrix H(n, n);

    Vector xp = x;
    Vector xm = x;

    double phix = phi(x);

    for (int i = 0; i < n; ++i) {
        double dxi = (1.0 + std::abs(x[i])) * std::pow(2.0, -17);

        xp[i] += dxi;
        xm[i] -= dxi;

        H(i, i) = (phi(xp) - 2.0 * phix + phi(xm)) / (dxi * dxi);

        xp[i] -= dxi;
        xm[i] += dxi;
    }

    for (int i = 0; i < n; ++i) {
        double dxi = (1.0 + std::abs(x[i])) * std::pow(2.0, -17);

        for (int j = i + 1; j < n; ++j) {
            double dxj = (1.0 + std::abs(x[j])) * std::pow(2.0, -17);

            Vector xpp = x;
            Vector xpm = x;
            Vector xmp = x;
            Vector xmm = x;

            xpp[i] += dxi; xpp[j] += dxj;
            xpm[i] += dxi; xpm[j] -= dxj;
            xmp[i] -= dxi; xmp[j] += dxj;
            xmm[i] -= dxi; xmm[j] -= dxj;

            double Hij =
                (phi(xpp) - phi(xpm) - phi(xmp) + phi(xmm))
                / (4.0 * dxi * dxj);

            H(i, j) = Hij;
            H(j, i) = Hij;
        }
    }

    return H;
}

Vector gradient(
    std::function<double(const Vector&)> phi,
    const Vector& x
) {
    int n = x.size();
    Vector g(n);

    Vector xp = x;
    Vector xm = x;

    for (int i = 0; i < n; ++i) {
        double dxi = (1.0 + std::abs(x[i])) * std::pow(2.0, -17);

        xp[i] += dxi;
        xm[i] -= dxi;

        g[i] = (phi(xp) - phi(xm)) / (2.0 * dxi);

        xp[i] -= dxi;
        xm[i] += dxi;
    }

    return g;
}


NewtonResult newton(
    std::function<double(const Vector&)> phi,
    Vector x,
    double acc,
    int max_iter
) {
    for (int k = 0; k < max_iter; ++k) {
        Vector g = gradient(phi, x);

        if (g.norm() < acc) {
            return {x, k, true};
        }

        Matrix H = hessian(phi, x);

        // Levenberg regularization
        for (int i = 0; i < H.rows(); ++i) {
            H(i, i) += 1e-6;
        }

        Vector rhs = g * (-1.0);

        QR qr(H);
        Vector dx = qr.solve(rhs);

        double lambda = 1.0;
        double phix = phi(x);

        while (lambda > 1.0 / 1024.0) {
            Vector z = x + lambda * dx;

            if (phi(z) < phix) {
                break;
            }

            lambda /= 2.0;
        }

        x += lambda * dx;
    }

    return {x, max_iter, false};
}

}