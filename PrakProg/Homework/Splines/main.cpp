#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>
#include "cubespline.h"
#include "quadspline.h"
#include "interp.h"

int main(int argc, char** argv) {
    std::string arg = argv[1];
    

    if (arg=="-opgaveA"){
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
    }


    if(arg == "-opgaveB"){
        std::vector<double> x , y;

    for (double xi = 0; xi <= 9.0; xi += 0.05) {
        
        x.push_back(xi);
        y.push_back(std::cos(xi));
    }

    qspline q(x, y);

    std::cout << std::fixed << std::setprecision(8);

    std::cout << "# z "
              << "cos(z) "
              << "linterp(z) "
              << "linteg(z) "
              << "qspline(z) "
              << "qderiv(z) "
              << "qinteg(z)\n";
              
    for (double z = x.front(); z <= x.back(); z += 0.02) {
        std::cout << z << " "
                  << std::cos(z) << " "
                  << linterp(x, y, z) << " "
                  << linterpInteg(x, y, z) << " "
                  << q.eval(z) << " "
                  << q.deriv(z) << " "
                  << q.integ(z) << "\n";
    }

    return 0;
}

if (arg == "-opgaveC") {
    std::vector<double> x, y;

    for (double xi = 0; xi <= 9.0; xi += 0.5) {
        x.push_back(xi);
        y.push_back(std::cos(xi));
    }

    cspline c(x, y);

    std::cout << std::fixed << std::setprecision(8);

    for (double z = x.front(); z <= x.back(); z += 0.02) {
        std::cout << z << " "
                  << std::cos(z) << " "
                  << c.eval(z) << " "
                  << c.deriv(z) << " "
                  << c.integ(z) << "\n";
    }

    return 0;
}



return 0;
}
