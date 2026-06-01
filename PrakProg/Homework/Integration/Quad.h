#pragma once
#include <functional>

namespace Quad {
    using Func = std::function<double(double)>;

    double integrate(
        Func f,
        double a,
        double b,
        double acc = 1e-6,
        double eps = 1e-6
    );
    
    double erf(double z, double acc = 1e-6, double eps = 1e-6);
}