#include "Quad.h"
#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    std::cout << std::setprecision(16);

    double acc = 1e-6;
    double eps = 1e-6;

    auto test = [&](const char* name, auto f, double exact) {
        double result = Quad::integrate(f, 0.0, 1.0, acc, eps);
        std::cout << name << "\n";
        std::cout << "result = " << result << "\n";
        std::cout << "exact  = " << exact << "\n";
        std::cout << "error  = " << std::abs(result - exact) << "\n\n";
    };

    test("int_0^1 sqrt(x) dx",
         [](double x) { return std::sqrt(x); },
         2.0 / 3.0);

    test("int_0^1 1/sqrt(x) dx",
         [](double x) { return 1.0 / std::sqrt(x); },
         2.0);

    test("int_0^1 4*sqrt(1-x*x) dx",
         [](double x) { return 4.0 * std::sqrt(1.0 - x * x); },
         M_PI);

    test("int_0^1 log(x)/sqrt(x) dx",
         [](double x) { return std::log(x) / std::sqrt(x); },
         -4.0);

    std::cout << "erf(1)\n";
    double erf1 = Quad::erf(1.0, acc, eps);
    double exact_erf1 = 0.84270079294971486934;

    std::cout << "result = " << erf1 << "\n";
    std::cout << "exact  = " << exact_erf1 << "\n";
    std::cout << "error  = " << std::abs(erf1 - exact_erf1) << "\n\n";

    std::cout << "# acc error\n";
    for (double a = 1e-1; a >= 1e-10; a *= 0.1) {
        double y = Quad::erf(1.0, a, 0.0);
        std::cout << a << " " << std::abs(y - exact_erf1) << "\n";
    }

    return 0;
}