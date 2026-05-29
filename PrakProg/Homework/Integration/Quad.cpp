#include "Quad.h"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace Quad {

static double adapt(
    const Func& f,
    double a,
    double b,
    double acc,
    double eps,
    double f2,
    double f3,
    int depth
) {
    if (depth <= 0)
        throw std::runtime_error("Maximum recursion depth reached");

    double h = b - a;

    if (std::isnan(f2)) {
        f2 = f(a + 2.0 * h / 6.0);
        f3 = f(a + 4.0 * h / 6.0);
    }

    double f1 = f(a + h / 6.0);
    double f4 = f(a + 5.0 * h / 6.0);

    double Q = (2.0 * f1 + f2 + f3 + 2.0 * f4) * h / 6.0;
    double q = (f1 + f2 + f3 + f4) * h / 4.0;

    double err = std::abs(Q - q);
    double tol = acc + eps * std::abs(Q);

    if (err <= tol)
        return Q;

    double m = 0.5 * (a + b);

    return adapt(f, a, m, acc / std::sqrt(2.0), eps, f1, f2, depth - 1)
         + adapt(f, m, b, acc / std::sqrt(2.0), eps, f3, f4, depth - 1);
}

double integrate(Func f, double a, double b, double acc, double eps) {
    if (a == b) return 0.0;

    if (b < a)
        return -integrate(f, b, a, acc, eps);

    double nan = std::numeric_limits<double>::quiet_NaN();

    return adapt(f, a, b, acc, eps, nan, nan, 100000);
}

double erf(double z, double acc, double eps) {
    const double sqrt_pi = std::sqrt(M_PI);

    if (z < 0)
        return -erf(-z, acc, eps);

    if (z <= 1.0) {
        auto f = [](double x) {
            return std::exp(-x * x);
        };

        return 2.0 / sqrt_pi * integrate(f, 0.0, z, acc, eps);
    }

    auto f = [z](double t) {
        return std::exp(-std::pow(z + (1.0 - t) / t, 2.0)) / (t * t);
    };

    return 1.0 - 2.0 / sqrt_pi * integrate(f, 0.0, 1.0, acc, eps);
}

}