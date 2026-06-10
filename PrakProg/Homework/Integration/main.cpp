#include "Quad.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <stdexcept>

int main() {
    std::cout << std::setprecision(16);

    double acc = 1e-6;
    double eps = 1e-6;

    std::cout << "===== ORDINARY INTEGRATOR TEST =====\n\n";

    {
        int calls = 0;

        auto f = [&](double x) {
            calls++;
            return x*x;
        };

        double result = Quad::integrate(f, 0.0, 1.0, acc, eps);
        double exact = 1.0/3.0;

        std::cout << "Integral[0,1] x^2 dx\n";
        std::cout << "result = " << result << "\n";
        std::cout << "exact  = " << exact << "\n";
        std::cout << "error  = " << std::abs(result - exact) << "\n";
        std::cout << "calls  = " << calls << "\n\n";
    }

    std::cout << "===== CLENSHAW-CURTIS TESTS =====\n\n";

    auto testCC = [&](const char* name, auto f, double exact) {
        int calls = 0;

        auto countedF = [&](double x) {
            calls++;
            return f(x);
        };

        try {
            double result = Quad::integrateCC(countedF, 0.0, 1.0, acc, eps);

            std::cout << name << "\n";
            std::cout << "result = " << result << "\n";
            std::cout << "exact  = " << exact << "\n";
            std::cout << "error  = " << std::abs(result - exact) << "\n";
            std::cout << "calls  = " << calls << "\n\n";
        }
        catch (const std::exception& e) {
            std::cout << name << "\n";
            std::cout << "FAILED: " << e.what() << "\n";
            std::cout << "calls before fail = " << calls << "\n\n";
        }
    };

    testCC(
        "Integral[0,1] sqrt(x) dx",
        [](double x) { return std::sqrt(x); },
        2.0/3.0
    );

    testCC(
        "Integral[0,1] 1/sqrt(x) dx",
        [](double x) { return 1.0/std::sqrt(x); },
        2.0
    );

    testCC(
        "Integral[0,1] 4*sqrt(1-x*x) dx",
        [](double x) { return 4.0*std::sqrt(1.0 - x*x); },
        M_PI
    );

    testCC(
        "Integral[0,1] log(x)/sqrt(x) dx",
        [](double x) { return std::log(x)/std::sqrt(x); },
        -4.0
    );

std::cout << "===== INFINITE LIMIT TESTS =====\n\n";

auto testInf = [&](const char* name, auto f, double a, double b, double exact) {
    int calls = 0;

    auto countedF = [&](double x) {
        calls++;
        return f(x);
    };

    try {
        double result = Quad::integrateCCInf(countedF, a, b, acc, eps);

        std::cout << name << "\n";
        std::cout << "result = " << result << "\n";
        std::cout << "exact  = " << exact << "\n";
        std::cout << "error  = " << std::abs(result - exact) << "\n";
        std::cout << "calls  = " << calls << "\n\n";
    }
    catch (const std::exception& e) {
        std::cout << name << "\n";
        std::cout << "FAILED: " << e.what() << "\n";
        std::cout << "calls before fail = " << calls << "\n\n";
    }
};

testInf(
    "Integral[0,infinity] exp(-x) dx",
    [](double x) {
        return std::exp(-x);
    },
    0.0,
    INFINITY,
    1.0
);

testInf(
    "Integral[0,infinity] 1/(1+x*x) dx",
    [](double x) {
        return 1.0/(1.0 + x*x);
    },
    0.0,
    INFINITY,
    M_PI/2.0
);

testInf(
    "Integral[-infinity,infinity] exp(-x*x) dx",
    [](double x) {
        return std::exp(-x*x);
    },
    -INFINITY,
    INFINITY,
    std::sqrt(M_PI)
);

testInf(
    "Integral[-infinity,infinity] 1/(1+x*x) dx",
    [](double x) {
        return 1.0/(1.0 + x*x);
    },
    -INFINITY,
    INFINITY,
    M_PI
);






    std::cout << "===== ERF TEST =====\n\n";

    double exactErf = 0.84270079294971486934;
    double erfResult = Quad::erf(1.0, acc, eps);

    std::cout << "erf(1)\n";
    std::cout << "result = " << erfResult << "\n";
    std::cout << "exact  = " << exactErf << "\n";
    std::cout << "error  = " << std::abs(erfResult - exactErf) << "\n\n";

    std::ofstream out("erf_accuracy.txt");

    for (double a = 1e-1; a >= 1e-12; a /= 10.0) {
        double y = Quad::erf(1.0, a, 0.0);
        double err = std::abs(y - exactErf);
        out << a << " " << err << "\n";
    }

    out.close();

    return 0;
}