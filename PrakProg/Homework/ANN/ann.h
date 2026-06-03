#pragma once
#include <vector>
#include <functional>

struct Ann {
    int n;
    std::vector<double> a, b, w;

    Ann(int n);

    double f(double z) const;
    double df(double z) const;
    double ddf(double z) const;

    double response(double x) const;
    double cost(const std::vector<double>& xs,
                const std::vector<double>& ys) const;

    void train(const std::vector<double>& xs,
               const std::vector<double>& ys,
               int steps = 10000,
               double eta = 0.001);
    
    double Fint(double z) const;
    double dresponse(double x) const;
    double ddresponse(double x) const;
    double antiDerivative(double x) const;
};