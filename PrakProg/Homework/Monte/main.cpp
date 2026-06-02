#include "mcarlo.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

void runCircle() {
    auto circle = [](const std::vector<double>& x) {
        double r2 = x[0] * x[0] + x[1] * x[1];
        return r2 <= 1.0 ? 1.0 : 0.0;
    };

    std::vector<double> lower2 = {-1.0, -1.0};
    std::vector<double> upper2 = { 1.0,  1.0};

    int N = 100000;
    LCG rng(12345);

    auto [area, err] = plainMC(circle, lower2, upper2, N, rng);

    std::cout << "Unit circle area estimate: " << area << "\n";
    std::cout << "Estimated error: " << err << "\n";
    std::cout << "Exact value pi: " << M_PI << "\n";
    std::cout << "Actual error: " << std::abs(area - M_PI) << "\n";
}

void runEllipsoid() {
    double A = 1.0, B = 2.0, C = 3.0;

    auto ellipsoid = [A, B, C](const std::vector<double>& x) {
        double value =
            x[0] * x[0] / (A * A) +
            x[1] * x[1] / (B * B) +
            x[2] * x[2] / (C * C);

        return value <= 1.0 ? 1.0 : 0.0;
    };

    std::vector<double> lower3 = {-A, -B, -C};
    std::vector<double> upper3 = { A,  B,  C};

    int N = 100000;
    LCG rng(12345);

    auto [vol, volErr] = plainMC(ellipsoid, lower3, upper3, N, rng);

    double exactVol = 4.0 / 3.0 * M_PI * A * B * C;

    std::cout << "Ellipsoid volume estimate: " << vol << "\n";
    std::cout << "Estimated error: " << volErr << "\n";
    std::cout << "Exact volume: " << exactVol << "\n";
    std::cout << "Actual error: " << std::abs(vol - exactVol) << "\n";
}

void makePlotDataA() {
    auto circle = [](const std::vector<double>& x) {
        double r2 = x[0] * x[0] + x[1] * x[1];
        return r2 <= 1.0 ? 1.0 : 0.0;
    };

    std::vector<double> lower2 = {-1.0, -1.0};
    std::vector<double> upper2 = { 1.0,  1.0};

    std::ofstream out("opgAplot.data");

    for (int N = 100; N <= 100000; N *= 2) {
        LCG rng(12345);

        auto [area, estimated_error] = plainMC(circle, lower2, upper2, N, rng);
        double actual_error = std::abs(area - M_PI);

        out << N << " "
            << estimated_error << " "
            << actual_error << "\n";
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Use:\n";
        std::cout << "./montecarlo circle\n";
        std::cout << "./montecarlo ellipsoid\n";
        std::cout << "./montecarlo plotA\n";
        std::cout << "./montecarlo all\n";
        return 1;
    }

    std::string arg = argv[1];

    if (arg == "-circle") {
        runCircle();
    }
    else if (arg == "-ellipsoid") {
        runEllipsoid();
    }
    else if (arg == "-plotA") {
        makePlotDataA();
    }
    else if (arg == "-all") {
        runCircle();
        std::cout << "\n";
        runEllipsoid();
        makePlotDataA();
    }
    else {
        std::cout << "Unknown argument: " << arg << "\n";
        return 1;
    }

    return 0;
}