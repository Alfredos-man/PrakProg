#include "ann.h"
#include <iostream>
#include <vector>
#include <cmath>

double g(double x) {
    return std::cos(5*x - 1) * std::exp(-x*x);
}

double dg(double x) {
    return std::exp(-x*x) *
           (-5*std::sin(5*x - 1) - 2*x*std::cos(5*x - 1));
}

int main() {
    std::vector<double> xs, ys;

    int N = 50;

    for (int i = 0; i < N; i++) {
        double x = -1.0 + 2.0*i/(N - 1.0);
        xs.push_back(x);
        ys.push_back(g(x));
    }

    Ann net(15);

    std::cerr << "Initial cost = " << net.cost(xs, ys) << "\n";

    net.train(xs, ys, 50000, 0.0001);

    std::cerr << "Final cost = " << net.cost(xs, ys) << "\n";

    std::cout << "# x g(x) ANN g'(x) ANN'(x) ANN''(x) antiANN(x)\n";

    for (double x = -1.0; x <= 1.0001; x += 0.05) {
        std::cout
            << x << " "
            << g(x) << " "
            << net.response(x) << " "
            << dg(x) << " "
            << net.dresponse(x) << " "
            << net.ddresponse(x) << " "
            << net.antiDerivative(x)
            << "\n";
    }

    return 0;
}