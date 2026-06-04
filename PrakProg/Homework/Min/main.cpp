#include "newton.h"
#include <iostream>
#include <cmath>

using namespace la;

int main() {

    // Rosenbrock
    auto rosenbrock = [](const Vector& v) {
        double x = v[0];
        double y = v[1];

        return std::pow(1.0 - x, 2)
             + 100.0 * std::pow(y - x * x, 2);
    };

    Vector x0_rosen = {-1.0, 2.0};

    NewtonResult rosen = newton(
        rosenbrock,
        x0_rosen,
        1e-3,
        1000
    );

    std::cout << "Rosenbrock:\n";
    std::cout << "Converged: " << rosen.converged << "\n";
    std::cout << "Iterations: " << rosen.iterations << "\n";
    std::cout << "Minimum at: ";
    rosen.x.print_vector();
    std::cout << "f(x) = " << rosenbrock(rosen.x) << "\n\n";


    // Himmelblau
    auto himmelblau = [](const Vector& v) {
        double x = v[0];
        double y = v[1];

        return std::pow(x * x + y - 11.0, 2)
             + std::pow(x + y * y - 7.0, 2);
    };

    Vector x0_himmel = {2.0, 2.0};

    NewtonResult himmel = newton(
        himmelblau,
        x0_himmel,
        1e-3,
        1000
    );

    std::cout << "Himmelblau:\n";
    std::cout << "Converged: " << himmel.converged << "\n";
    std::cout << "Iterations: " << himmel.iterations << "\n";
    std::cout << "Minimum at: ";
    himmel.x.print_vector();
    std::cout << "f(x) = " << himmelblau(himmel.x) << "\n";

    return 0;
}