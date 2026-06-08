#include <iostream>
#include <string>
#include <cmath>
#include "ODE.h"

int main(int argc, char** argv) {

    //opgaveA
    if(argc > 1 && std::string(argv[1])=="-opgaveA") {
        

        // u'' = -u
        odefun f = [](double x, const vec& y) {
            return vec{y[1], -y[0]};
        };

        vec y0 = {1.0, 0.0};

        auto [xs, ys] = driver(f, 0.0, y0, 10.0);

        for(size_t i = 0; i < xs.size(); i++) {
            std::cout << xs[i] << " " << ys[i][0] << "\n";
        }
    }

    //opgaveB
if(argc > 2 && std::string(argv[1]) == "-opgaveB") {
    int delopgave = std::stoi(argv[2]);

    double eps;
    vec y0;

    if(delopgave == 1) {
        // Eksakt cirkulær løsning: u(phi)=1
        for(double phi = 0; phi <= 50*M_PI; phi += 0.01) {
            std::cout << phi << " " << 1.0 << "\n";
        }
        return 0;
    }
    else if(delopgave == 2) {
        eps = 0.0;
        y0 = {1.0, -0.5};
    }
    else if(delopgave == 3) {
        eps = 0.01;
        y0 = {1.0, -0.5};
    }
    else {
        std::cerr << "Ukendt delopgave B: " << delopgave << "\n";
        return 1;
    }

    odefun f = [eps](double phi, const vec& y) {
        return vec{
            y[1],
            1 - y[0] + eps*y[0]*y[0]
        };
    };

    auto [phis, ys] = driver(
        f,
        0.0,
        y0,
        50*M_PI,
        0.01,
        1e-8,
        1e-8
    );

    for(size_t i = 0; i < phis.size(); i++) {
        std::cout << phis[i] << " " << ys[i][0] << "\n";
    }

    return 0;
}

    return 0;
}