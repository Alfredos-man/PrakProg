#include "newton.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace la;

// ---------- OPGAVE 1 ----------

double rosenbrock(const Vector& x) {
    double X = x[0], Y = x[1];
    return (1-X)*(1-X) + 100*(Y-X*X)*(Y-X*X);
}

double himmelblau(const Vector& x) {
    double X = x[0], Y = x[1];
    return std::pow(X*X + Y - 11, 2)
         + std::pow(X + Y*Y - 7, 2);
}

void run_opgave1() {
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
}


// ---------- OPGAVE 2 ----------

struct State {
    double f;
    double fp;
};

State rhs(double r, const State& y, double E) {
    State dy;

    dy.f = y.fp;
    dy.fp = -2.0 * (E + 1.0/r) * y.f;

    return dy;
}

State rk4_step(double r, const State& y, double h, double E) {
    State k1 = rhs(r, y, E);

    State y2{
        y.f  + 0.5*h*k1.f,
        y.fp + 0.5*h*k1.fp
    };
    State k2 = rhs(r + 0.5*h, y2, E);

    State y3{
        y.f  + 0.5*h*k2.f,
        y.fp + 0.5*h*k2.fp
    };
    State k3 = rhs(r + 0.5*h, y3, E);

    State y4{
        y.f  + h*k3.f,
        y.fp + h*k3.fp
    };
    State k4 = rhs(r + h, y4, E);

    State ynext;

    ynext.f = y.f + h/6.0 * (
        k1.f + 2.0*k2.f + 2.0*k3.f + k4.f
    );

    ynext.fp = y.fp + h/6.0 * (
        k1.fp + 2.0*k2.fp + 2.0*k3.fp + k4.fp
    );

    return ynext;
}

double shoot(double E, double rmin, double rmax, double h, bool save=false) {
    State y;

    y.f  = rmin - rmin*rmin;
    y.fp = 1.0 - 2.0*rmin;

    std::ofstream file;

    if (save) {
        file.open("wavefunction.txt");
    }

    for (double r = rmin; r < rmax; r += h) {
        if (save) {
            double exact = r * std::exp(-r);
            file << r << " " << y.f << " " << exact << "\n";
        }

        if (r + h > rmax) {
            h = rmax - r;
        }

        y = rk4_step(r, y, h, E);
    }

    return y.f;
}

double bisection(double a, double b, double rmin, double rmax, double h) {
    double fa = shoot(a, rmin, rmax, h);
    double fb = shoot(b, rmin, rmax, h);

    if (fa * fb > 0) {
        std::cerr << "Error: root is not bracketed.\n";
        std::cerr << "M(" << a << ") = " << fa << "\n";
        std::cerr << "M(" << b << ") = " << fb << "\n";
        return NAN;
    }

    for (int i = 0; i < 100; i++) {
        double c = 0.5 * (a + b);
        double fc = shoot(c, rmin, rmax, h);

        if (std::abs(fc) < 1e-10 || std::abs(b - a) < 1e-10) {
            return c;
        }

        if (fa * fc < 0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
    }

    return 0.5 * (a + b);
}

void run_opgave2() {
    double rmin = 1e-4;
    double rmax = 8.0;
    double h = 1e-3;

    double E0 = bisection(-0.7, -0.3, rmin, rmax, h);

    std::cout << "Hydrogen shooting method:\n";
    std::cout << "rmin = " << rmin << "\n";
    std::cout << "rmax = " << rmax << "\n";
    std::cout << "h    = " << h << "\n\n";

    std::cout << "Numerical E0 = " << E0 << "\n";
    std::cout << "Exact E0     = -0.5\n";
    std::cout << "Error        = " << std::abs(E0 + 0.5) << "\n";

    shoot(E0, rmin, rmax, h, true);

    std::cout << "\nSaved wavefunction to wavefunction.txt\n";
}


// ---------- MAIN ----------

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Brug:\n";
        std::cout << "  ./main opgave1\n";
        std::cout << "  ./main opgave2\n";
        return 1;
    }

    std::string choice = argv[1];

    if (choice == "-opgave1") {
        run_opgave1();
    }
    else if (choice == "-opgave2") {
        run_opgave2();
    }
    else {
        std::cerr << "Ukendt opgave: " << choice << "\n";
        std::cerr << "Brug enten:\n";
        std::cerr << "  ./main opgave1\n";
        std::cerr << "  ./main opgave2\n";
        return 1;
    }

    return 0;
}