#include "mcarlo.h"
#include <cmath>

LCG::LCG(unsigned long long seed)
    : seed(seed), a(1664525), c(1013904223), m(1ULL << 32) {}

double LCG::operator()() {
    seed = (a * seed + c) % m;
    return static_cast<double>(seed + 1) / static_cast<double>(m + 1);
}

std::pair<double, double> plainMC(
    const std::function<double(const std::vector<double>&)>& f,
    const std::vector<double>& lower,
    const std::vector<double>& upper,
    int N,
    LCG& rng
) {
    int dim = lower.size();

    double volume = 1.0;
    for (int i = 0; i < dim; ++i) {
        volume *= upper[i] - lower[i];
    }

    double sum = 0.0;
    double sum2 = 0.0;

    for (int n = 0; n < N; ++n) {
        std::vector<double> x(dim);

        for (int i = 0; i < dim; ++i) {
            x[i] = lower[i] + rng() * (upper[i] - lower[i]);
        }

        double fx = f(x);
        sum += fx;
        sum2 += fx * fx;
    }

    double mean = sum / N;
    double sigma = std::sqrt(sum2 / N - mean * mean);

    double integral = mean * volume;
    double error = sigma * volume / std::sqrt(N);

    return {integral, error};
}