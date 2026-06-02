#ifndef MCARLO_H
#define MCARLO_H

#include <vector>
#include <functional>
#include <utility>

class LCG {
private:
    unsigned long long seed;
    unsigned long long a, c, m;

public:
    LCG(unsigned long long seed);
    double operator()();
};

std::pair<double, double> plainMC(
    const std::function<double(const std::vector<double>&)>& f,
    const std::vector<double>& lower,
    const std::vector<double>& upper,
    int N,
    LCG& rng
);

#endif