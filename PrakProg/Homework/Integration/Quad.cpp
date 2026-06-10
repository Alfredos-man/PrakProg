#include "Quad.h"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace Quad {

static Result adapt(
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
        return {Q, err};

    double m = 0.5 * (a + b);

    Result left =
        adapt(f, a, m, acc / std::sqrt(2.0), eps, f1, f2, depth - 1);

    Result right =
        adapt(f, m, b, acc / std::sqrt(2.0), eps, f3, f4, depth - 1);

    return {
        left.value + right.value,
        std::sqrt(left.error * left.error + right.error * right.error)
    };
}

Result integrateWithError(Func f, double a, double b, double acc, double eps) {
    if (a == b)
        return {0.0, 0.0};

    if (b < a) {
        Result r = integrateWithError(f, b, a, acc, eps);
        return {-r.value, r.error};
    }

    double nan = std::numeric_limits<double>::quiet_NaN();

    return adapt(f, a, b, acc, eps, nan, nan, 10000);
}

double integrate(Func f, double a, double b, double acc, double eps) {
    return integrateWithError(f, a, b, acc, eps).value;
}

Result integrateCCWithError(Func f, double a, double b, double acc, double eps) {
    auto g = [=](double theta) {
        if (theta == 0.0 || theta == M_PI)
            return 0.0;

        double x = (a+b)/2.0 + (b-a)/2.0 * std::cos(theta);

        return f(x) * std::sin(theta) * (b-a)/2.0;
    };

    return integrateWithError(g, 0.0, M_PI, acc, eps);
}

double integrateCC(Func f, double a, double b, double acc, double eps) {
    return integrateCCWithError(f, a, b, acc, eps).value;
}

double integrateCCInf(Func f, double a, double b, double acc, double eps) {
    if (std::isinf(a) && std::isinf(b)) {
        auto g = [=](double t) {
            double x = t / (1.0 - t*t);
            double dxdt = (1.0 + t*t) / std::pow(1.0 - t*t, 2);
            return f(x) * dxdt;
        };

        return integrateCC(g, -1.0, 1.0, acc, eps);
    }

    if (std::isinf(b)) {
        auto g = [=](double t) {
            double x = a + t / (1.0 - t);
            double dxdt = 1.0 / std::pow(1.0 - t, 2);
            return f(x) * dxdt;
        };

        return integrateCC(g, 0.0, 1.0, acc, eps);
    }

    if (std::isinf(a)) {
        auto g = [=](double t) {
            double x = b - (1.0 - t) / t;
            double dxdt = 1.0 / (t*t);
            return f(x) * dxdt;
        };

        return integrateCC(g, 0.0, 1.0, acc, eps);
    }

    return integrateCC(f, a, b, acc, eps);
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