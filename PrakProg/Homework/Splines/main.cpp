#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "interp.h"

int main() {
    std::vector<double> x;
    std::vector<double> y;

    for (double xi = 0; xi <= 9.0; xi += 0.5) {
        x.push_back(xi);
        y.push_back(cos(xi));
    }

    std::cout << std::fixed << std::setprecision(6);


    for (double z = 0; z <= 9.0; z += 0.25) {
        std::cout << std::setw(10) << z
                  << std::setw(15) << linterp(x, y, z)
                  << std::setw(15) << linterpInteg(x, y, z)
                  << "\n";
    }

    return 0;
}