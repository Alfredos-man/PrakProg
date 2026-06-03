#pragma once
#include <vector>
#include <functional>

struct Ann {
    int n;
    std::vector<double> a, b, w;

    Ann(int n);

    double f(double z) const;
    double df(double z) const;

    double response(double x) const;
    double cost(const std::vector<double>& xs,
                const std::vector<double>& ys) const;

    void train(const std::vector<double>& xs,
               const std::vector<double>& ys,
               int steps = 10000,
               double eta = 0.001);
};