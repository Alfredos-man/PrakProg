#include "newton.h"
#include <iostream>
#include <cmath>

using namespace la;

double rosenbrock(const Vector& x) {
    double X = x[0], Y = x[1];
    return (1-X)*(1-X) + 100*(Y-X*X)*(Y-X*X);
}

double himmelblau(const Vector& x) {
    double X = x[0], Y = x[1];
    return std::pow(X*X + Y - 11, 2)
         + std::pow(X + Y*Y - 7, 2);
}

int main() {
    auto rosen_grad = [](const Vector& x) {
        Vector g(2);
        double X = x[0], Y = x[1];

        g[0] = -2*(1-X) - 400*X*(Y-X*X);
        g[1] = 200*(Y-X*X);

        return g;
    };

    auto rosen_hess = [](const Vector& x) {
        Matrix H(2,2);
        double X = x[0], Y = x[1];

        H(0,0) = 2 - 400*Y + 1200*X*X;
        H(0,1) = -400*X;
        H(1,0) = -400*X;
        H(1,1) = 200;

        return H;
    };

    std::cout << "Rosenbrock:\n";
    Vector r0{-1.2, 1.0};
    NewtonResult r = newton(rosen_grad, rosen_hess, r0);

    std::cout << "x = ";
    r.x.print_vector();
    std::cout << "f(x) = " << rosenbrock(r.x) << "\n";
    std::cout << "iterations = " << r.iterations << "\n";
    std::cout << "converged = " << r.converged << "\n\n";


    auto himmel_grad = [](const Vector& x) {
        Vector g(2);
        double X = x[0], Y = x[1];

        double a = X*X + Y - 11;
        double b = X + Y*Y - 7;

        g[0] = 4*X*a + 2*b;
        g[1] = 2*a + 4*Y*b;

        return g;
    };

    auto himmel_hess = [](const Vector& x) {
        Matrix H(2,2);
        double X = x[0], Y = x[1];

        H(0,0) = 12*X*X + 4*Y - 42;
        H(0,1) = 4*X + 4*Y;
        H(1,0) = 4*X + 4*Y;
        H(1,1) = 4*X + 12*Y*Y - 26;

        return H;
    };

    std::cout << "Himmelblau:\n";

    Vector starts[] = {
        Vector{3.0, 2.0},
        Vector{-3.0, 3.0},
        Vector{-4.0, -3.0},
        Vector{4.0, -2.0}
    };

    for (Vector x0 : starts) {
        NewtonResult h = newton(himmel_grad, himmel_hess, x0);

        std::cout << "x = ";
        h.x.print_vector();
        std::cout << "f(x) = " << himmelblau(h.x) << "\n";
        std::cout << "iterations = " << h.iterations << "\n";
        std::cout << "converged = " << h.converged << "\n\n";
    }

    return 0;
}