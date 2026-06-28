#include "mcarlo.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <random>

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

    for (int N = 100; N <= 1000000; N *= 2) {
        LCG rng(12345);

        auto [area, estimated_error] = plainMC(circle, lower2, upper2, N, rng);
        double actual_error = std::abs(area - M_PI);

        out << N << " "
            << estimated_error << " "
            << actual_error << "\n";
    }

}

void makePlotDataB() {

    auto difficult = [](const std::vector<double>& u) {
        double x = M_PI*u[0];
        double y = M_PI*u[1];
        double z = M_PI*u[2];

        return 1.0 /
            (1.0 - std::cos(x)*std::cos(y)*std::cos(z));
    };

    std::vector<double> lower = {0.0,0.0,0.0};
    std::vector<double> upper = {1.0,1.0,1.0};

    double exact = 1.3932039296856768591842462603255;

    std::ofstream out("opgBplot.data");

    for (int N = 100; N <= 100000; N *= 2) {

        LCG rng(12345);

        auto [lcg, lcgErr] = plainMC(difficult, lower, upper, N, rng);
        auto [stdmc, stdErr] = stdMC(difficult, lower, upper, N);
        auto [halton, quasiErr] = quasiMC(difficult, lower, upper, N);

        out << N << " "
            << std::abs(lcg - exact) << " "
            << std::abs(stdmc - exact) << " "
            << std::abs(halton - exact)
            << "\n";
    }
}

void runQuasi() {
    auto smooth3D = [](const std::vector<double>& x) {
        return x[0] * x[1] * x[2];
    };

    std::vector<double> lower = {0.0, 0.0, 0.0};
    std::vector<double> upper = {1.0, 1.0, 1.0};

    int N = 100000;

    auto [result, error] = quasiMC(smooth3D, lower, upper, N);

    double exact = 1.0 / 8.0;

    std::cout << "Quasi-MC result: " << result << "\n";
    std::cout << "Exact result:    " << exact << "\n";
    std::cout << "Actual error:    " << std::abs(result - exact) << "\n";
}

void compare() {
    auto difficult = [](const std::vector<double>& u) {
        double x = M_PI * u[0];
        double y = M_PI * u[1];
        double z = M_PI * u[2];

        return 1.0 / (1.0 - std::cos(x) * std::cos(y) * std::cos(z));
    };

    std::vector<double> lower = {0.0, 0.0, 0.0};
    std::vector<double> upper = {1.0, 1.0, 1.0};

    int N = 100000;
    double exact = 1.3932039296856768591842462603255;

    LCG rng(12345);
    auto [lcgResult, lcgError] = plainMC(difficult, lower, upper, N, rng);

    auto [stdResult, stdError] = stdMC(difficult, lower, upper, N);

    auto [quasiResult, quasiError] = quasiMC(difficult, lower, upper, N);

    std::cout << "Difficult integral comparison, N = " << N << "\n\n";

    std::cout << "LCG result:        " << lcgResult << "\n";
    std::cout << "LCG estimated err: " << lcgError << "\n";
    std::cout << "LCG actual err:    " << std::abs(lcgResult - exact) << "\n\n";

    std::cout << "std::mt19937 result:        " << stdResult << "\n";
    std::cout << "std::mt19937 estimated err: " << stdError << "\n";
    std::cout << "std::mt19937 actual err:    " << std::abs(stdResult - exact) << "\n\n";

    std::cout << "Halton result:     " << quasiResult << "\n";
    std::cout << "Halton actual err: " << std::abs(quasiResult - exact) << "\n\n";

    std::cout << "Exact value:       " << exact << "\n";
}

int main(int argc, char** argv) {

    if (argc < 2) {
        std::cout << "Usage:\n";
        std::cout << "./main -circle\n";
        std::cout << "./main -ellipsoid\n";
        std::cout << "./main -plotA\n";
        std::cout << "./main -quasi\n";
        std::cout << "./main -compare\n";
        std::cout << "./main -plotB\n";
        std::cout << "./main -all\n";
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
    else if (arg == "-quasi") {
        runQuasi();
    }
    else if (arg == "-compare") {
        compare();
    }
    else if (arg == "-plotB") {
        makePlotDataB();
    }
    else if (arg == "-all") {

        runCircle();
        std::cout << "\n";

        runEllipsoid();
        std::cout << "\n";

        runQuasi();
        std::cout << "\n";

        compare();

        makePlotDataA();
        makePlotDataB();
    }
    else {
        std::cout << "Unknown argument: " << arg << "\n";
        return 1;
    }

    return 0;

}