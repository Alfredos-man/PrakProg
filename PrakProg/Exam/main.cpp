
#include "rank.h"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

void runTest(const std::vector<double>& d,
             const std::vector<double>& u,
             const std::string& name)
{
    std::cout << "\n=== " << name << " ===\n";

    try {
        auto eig = rank1Eigenvalues(d, u);

        std::cout << std::setprecision(15);

        std::cout << "d: ";
        for (double x : d)
            std::cout << x << " ";

        std::cout << "\n";

        std::cout << "u: ";
        for (double x : u)
            std::cout << x << " ";

        std::cout << "\n";

        std::cout << "Eigenvalues:\n";
        for (double x : eig)
            std::cout << x << "\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << "\n";
    }
}

void runBenchmark()
{
    std::ofstream file("benchmark.data");

    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(0.0,1.0);

    //std::cout << "test at den kører kompilere rigtigt" << std::endl;

    for(int n=100; n<=5000; n+=100)
    {
        std::vector<double> d(n);
        std::vector<double> u(n);

        for(int i=0;i<n;i++)
        {
            d[i]=i+1;
            u[i]=dist(gen);
        }

        auto start =
            std::chrono::high_resolution_clock::now();

        rank1Eigenvalues(d,u);

        auto stop =
            std::chrono::high_resolution_clock::now();

        double t =
            std::chrono::duration<double,std::milli>(stop-start).count();

        file << n << " "
             << t << " "
             << n*n << "\n";

        std::cout << "n = "
                  << n
                  << " finished\n";
    }

    std::cout << "Benchmark written to benchmark.data\n";
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cout << "Usage:\n";
        std::cout << "./rank opg1\n";
        std::cout << "./rank plot\n";
        return 1;
    }

    std::string mode = argv[1];

    if(mode == "-tests")
    {
        runTest(
            {1.0,3.0,5.0},
            {1.0,2.0,1.0},
            "Basic 3x3");

        runTest(
            {1.0,2.0,4.0,8.0},
            {1.0,1.0,1.0,1.0},
            "All ones u");

        runTest(
            {10.0},
            {3.0},
            "1x1");

        runTest(
            {5.0,1.0,3.0},
            {1.0,1.0,2.0},
            "Unsorted d");

        runTest(
            {-2.0,0.0,4.0},
            {1.0,2.0,3.0},
            "Negative d");

        runTest(
            {1.0,10.0,100.0},
            {0.1,0.2,0.3},
            "Small update");
    }
    else if(mode == "-plot")
    {
        runBenchmark();
    }
    else
    {
        std::cout << "Unknown option: " << mode << "\n";
    }

    return 0;
}

