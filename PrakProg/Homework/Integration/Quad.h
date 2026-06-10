#pragma once
#include <functional>

namespace Quad {
    using Func = std::function<double(double)>;

    struct Result {
        double value;
        double error;
    };

    Result integrateWithError(
        Func f,
        double a,
        double b,
        double acc = 1e-6,
        double eps = 1e-6
    );

    double integrate(
        Func f,
        double a,
        double b,
        double acc = 1e-6,
        double eps = 1e-6
    );

    double integrateCC(
        Func f,
        double a,
        double b,
        double acc = 1e-6,
        double eps = 1e-6
    );

    double integrateCCInf(
        Func f,
        double a,
        double b,
        double acc = 1e-6,
        double eps = 1e-6
    );

    double erf(double z, double acc = 1e-6, double eps = 1e-6);
}