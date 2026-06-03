#include "ann.h"
#include <cmath>
#include <iostream>

Ann::Ann(int n) : n(n), a(n), b(n), w(n) {
    for (int i = 0; i < n; i++) {
        a[i] = -1.0 + 2.0 * i / (n - 1.0);
        b[i] = 0.3;
        w[i] = 0.1;
    }
}

double Ann::f(double z) const {
    return std::cos(5.0 * z) * std::exp(-z * z);
}

double Ann::df(double z) const {
    return std::exp(-z * z) *
           (-5.0 * std::sin(5.0 * z) - 2.0 * z * std::cos(5.0 * z));
}

double Ann::response(double x) const {
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        double z = (x - a[i]) / b[i];
        sum += w[i] * f(z);
    }

    return sum;
}

double Ann::cost(const std::vector<double>& xs,
                 const std::vector<double>& ys) const {
    double s = 0.0;

    for (int k = 0; k < xs.size(); k++) {
        double r = response(xs[k]) - ys[k];
        s += r * r;
    }

    return s;
}

void Ann::train(const std::vector<double>& xs,
                const std::vector<double>& ys,
                int steps,
                double eta) {
    for (int step = 0; step < steps; step++) {
        std::vector<double> ga(n, 0.0);
        std::vector<double> gb(n, 0.0);
        std::vector<double> gw(n, 0.0);

        for (int k = 0; k < xs.size(); k++) {
            double x = xs[k];
            double y = ys[k];

            double Fx = response(x);
            double r = Fx - y;

            for (int i = 0; i < n; i++) {
                double z = (x - a[i]) / b[i];

                gw[i] += 2.0 * r * f(z);
                ga[i] += 2.0 * r * w[i] * df(z) * (-1.0 / b[i]);
                gb[i] += 2.0 * r * w[i] * df(z) *
                         (-(x - a[i]) / (b[i] * b[i]));
            }
        }

        for (int i = 0; i < n; i++) {
            a[i] -= eta * ga[i];
            b[i] -= eta * gb[i];
            w[i] -= eta * gw[i];

            if (std::abs(b[i]) < 1e-6) {
                b[i] = 1e-6;
            }
        }

        if (step % 1000 == 0) {
            std::cerr << "step " << step
                      << " cost = " << cost(xs, ys) << "\n";
        }
    }
}