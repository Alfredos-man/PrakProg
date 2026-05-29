#ifndef ODE_H
#define ODE_H

#include <vector>
#include <functional>
#include <tuple>

using vec = std::vector<double>;
using odefun = std::function<vec(double, const vec&)>;

// Embedded Runge-Kutta 4(5) Dormand-Prince stepper
std::tuple<vec, vec> rkstep45(
    odefun f,
    double x,
    const vec& y,
    double h
);

// Adaptive driver
std::tuple<std::vector<double>, std::vector<vec>> driver(
    odefun f,
    double a,
    const vec& ya,
    double b,
    double h = 0.125,
    double acc = 1e-6,
    double eps = 1e-6
);

#endif