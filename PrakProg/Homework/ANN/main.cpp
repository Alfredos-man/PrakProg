#include "ann.h"
#include <iostream>
#include <vector>
#include <cmath>

double g(double x) {
    return x*x; //activation function (Den vi ville finde)
}

int main() {

    // Træningsdata
    std::vector<double> xs;
    std::vector<double> ys;

    int N = 50;

    for (int i = 0; i < N; i++) {
        double x = -1.0 + 2.0*i/(N-1);
        xs.push_back(x);
        ys.push_back(g(x));
    }

    // Opret netværk med 10 hidden neuroner
    Ann net(10);

    std::cout << "Initial cost = "
              << net.cost(xs, ys)
              << std::endl;

    // Træn
    net.train(xs, ys, 10000, 0.001);

    std::cout << "Final cost = "
              << net.cost(xs, ys)
              << std::endl;

    // Udskriv sammenligning
    std::cout << "\n# x  exact  network\n";

    for (double x = -1.0; x <= 5.0; x += 0.1) {
        std::cout
            << x << " "
            << g(x) << " "
            << net.response(x)
            << "\n";
    }

    return 0;
}