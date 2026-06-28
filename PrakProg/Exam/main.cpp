#include "rank.h"

#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>

void runTest(const std::vector<double>& d,
             const std::vector<double>& u,
             const std::string& name)
{
    std::cout << "\n=== " << name << " ===\n";

    try {
        auto eig = rank1Eigenvalues(d, u);

        std::cout << std::setprecision(15);
        std::cout << "d: ";
        for (double x : d) std::cout << x << " ";
        std::cout << "\n";

        std::cout << "u: ";
        for (double x : u) std::cout << x << " ";
        std::cout << "\n";

        std::cout << "eigenvalues:\n";
        for (double x : eig) {
            std::cout << x << "\n";
        }
    }
    catch (const std::exception& e) {
        std::cout << "ERROR: " << e.what() << "\n";
    }
}

int main()
{
    runTest(
        {1.0, 3.0, 5.0},
        {1.0, 2.0, 1.0},
        "Basic 3x3"
    );

    runTest(
        {1.0, 2.0, 4.0, 8.0},
        {1.0, 1.0, 1.0, 1.0},
        "All ones u"
    );

    runTest(
        {10.0},
        {3.0},
        "1x1 case"
    );

    runTest(
        {5.0, 1.0, 3.0},
        {1.0, 1.0, 2.0},
        "Unsorted d"
    );

    runTest(
        {-2.0, 0.0, 4.0},
        {1.0, 2.0, 3.0},
        "Negative and positive d"
    );

    runTest(
        {1.0, 10.0, 100.0},
        {0.1, 0.2, 0.3},
        "Small update"
    );

    return 0;
}