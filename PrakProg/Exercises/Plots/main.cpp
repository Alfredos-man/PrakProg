#include "funcs.h"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    double xmin = -5, xmax = 10, dx = 0.01;
    std::string func = "erf";

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-xmin" && i + 1 < argc) {
            xmin = std::stod(argv[++i]);
        }
        else if (arg == "-xmax" && i + 1 < argc) {
            xmax = std::stod(argv[++i]);
        }
        else if (arg == "-dx" && i + 1 < argc) {
            dx = std::stod(argv[++i]);
        }
        else if (arg == "-func" && i + 1 < argc) {
            func = argv[++i];
        }
    }

    std::cerr << "xmin = " << xmin << "\n";
    std::cerr << "xmax = " << xmax << "\n";
    std::cerr << "dx   = " << dx << "\n";
    std::cerr << "func = " << func << "\n";

    std::cout << std::scientific;

    if (func == "erf") {
        for (double x = xmin; x <= xmax; x += dx) {
            std::cout << x << " " << myerf(x) << "\n";
        }
    }
    else if (func == "sgamma") {
        for (double x = xmin; x <= xmax; x += dx) {
            std::cout << x << " " << sgamma(x) << "\n";
        }
    }
    else if (func == "lngamma") {
        for (double x = xmin; x <= xmax; x += dx) {
            std::cout << x << " " << lngamma(x) << "\n";
        }
    }
    else {
        std::cerr << "Ukendt funktion: " << func << "\n";
        return 1;
    }

    return 0;
}