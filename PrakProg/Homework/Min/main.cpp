#include "newton.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace la;

int main(int argc, char** argv) {

    if(argc < 2){
        std::cerr << "Usage:\n";
        std::cerr << "./main opgave1\n";
        std::cerr << "./main opgave2 < cern.data\n";
        return 1;
    }

    std::string mode = argv[1];

    if(mode == "opgave1") {

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
    }

    else if(mode == "opgave2") {

        std::vector<double> energy, signal, error;
        double E, s, ds;

        while(std::cin >> E >> s >> ds){
            energy.push_back(E);
            signal.push_back(s);
            error.push_back(ds);
        }

        auto breit_wigner = [](double E, double m, double Gamma, double A) {
            return A / ((E - m)*(E - m) + Gamma*Gamma/4.0);
        };

        auto deviation = [&](const Vector& v) {
            double m = v[0];
            double Gamma = v[1];
            double A = v[2];

            double sum = 0.0;

            for(size_t i = 0; i < energy.size(); ++i){
                double F = breit_wigner(energy[i], m, Gamma, A);
                double r = (F - signal[i]) / error[i];
                sum += r*r;
            }

            return sum;
        };

        Vector x0 = {125.0, 5.0, 20.0};

        NewtonResult fit = newton(
            deviation,
            x0,
            1e-3,
            1000
        );

        double m = fit.x[0];
        double Gamma = fit.x[1];
        double A = fit.x[2];

        std::cerr << "Higgs fit:\n";
        std::cerr << "Converged: " << fit.converged << "\n";
        std::cerr << "Iterations: " << fit.iterations << "\n";
        std::cerr << "m = " << m << "\n";
        std::cerr << "Gamma = " << Gamma << "\n";
        std::cerr << "A = " << A << "\n";
        std::cerr << "D = " << deviation(fit.x) << "\n";

        for(double e = 100.0; e <= 160.0; e += 0.1){
            std::cout << e << " " << breit_wigner(e, m, Gamma, A) << "\n";
        }
    }

    else {
        std::cerr << "Unknown mode: " << mode << "\n";
        return 1;
    }

    return 0;
}