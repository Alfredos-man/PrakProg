#include <iostream>
#include <cmath>
#include <vector>
#include "QR.h"
#include "lsfit.h"

int main() {
    la::Vector t  = {1, 2, 3, 4, 6, 9, 10, 13, 15};
    la::Vector y  = {117, 100, 88, 72, 53, 29.5, 25.2, 15.2, 11.1};
    la::Vector dy = {6, 5, 4, 4, 4, 3, 3, 2, 2};

    int n = t.size();

    la::Vector logy(n);
    la::Vector dlogy(n);

    for (int i = 0; i < n; ++i) {
        logy[i] = std::log(y[i]);
        dlogy[i] = dy[i] / y[i];
    }

    std::vector<la::Func> fs = {
        [](double x) { return 1.0; },
        [](double x) { return x; }
    };

    la::Vector c = la::lsfit(fs, t, logy, dlogy);

    double ln_a = c[0];
    double slope = c[1];

    double a = std::exp(ln_a);
    double lambda = -slope;
    double T_half = std::log(2.0) / lambda;

    std::cout << "ln(a)   = " << ln_a << "\n";
    std::cout << "a       = " << a << "\n";
    std::cout << "slope   = " << slope << "\n";
    std::cout << "lambda  = " << lambda << "\n";
    std::cout << "T_1/2   = " << T_half << " days\n";

    return 0;
}