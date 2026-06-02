#include "mcarlo.h"
#include <cmath>
#include<random>

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

// opgave B
double corput(int n, int base) {
    double q = 0.0;
    double bk = 1.0 / base;

    while (n > 0) {
        q += (n % base) * bk;
        n /= base;
        bk /= base;
    }

    return q;
}

std::vector<double> haltonPoint(int n, int dim) {
    static const int primes[] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29
    };

    std::vector<double> point(dim);

    for (int i = 0; i < dim; ++i) {
        point[i] = corput(n, primes[i]);
    }

    return point;
}

std::pair<double,double> quasiMC(
    const std::function<double(const std::vector<double>&)>& f,
    const std::vector<double>& lower,
    const std::vector<double>& upper,
    int N
) {
    int dim = lower.size();

    double volume = 1.0;
    for (int i = 0; i < dim; ++i) {
        volume *= upper[i] - lower[i];
    }

    double sum = 0.0;

    for (int n = 1; n <= N; ++n) {
        std::vector<double> u = haltonPoint(n, dim);
        std::vector<double> x(dim);

        for (int i = 0; i < dim; ++i) {
            x[i] = lower[i] + u[i] * (upper[i] - lower[i]);
        }

        sum += f(x);
    }

    double integral = volume * sum / N;

    return {integral, 0.0};
}

std::pair<double,double> stdMC(
    const std::function<double(const std::vector<double>&)>& f,
    const std::vector<double>& lower,
    const std::vector<double>& upper,
    int N
) {
    int dim = lower.size();

    double volume = 1.0;
    for(int i = 0; i < dim; i++) {
        volume *= upper[i] - lower[i];
    }

    std::mt19937 gen(12345);
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    double sum = 0.0;
    double sum2 = 0.0;

    for(int n = 0; n < N; n++) {
        std::vector<double> x(dim);

        for(int i = 0; i < dim; i++) {
            x[i] = lower[i]
                 + dist(gen)*(upper[i]-lower[i]);
        }

        double fx = f(x);

        sum += fx;
        sum2 += fx*fx;
    }

    double mean = sum/N;
    double sigma = std::sqrt(sum2/N - mean*mean);

    double integral = mean*volume;
    double error = sigma*volume/std::sqrt(N);

    return {integral,error};
}