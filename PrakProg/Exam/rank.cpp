#include "rank.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace {

struct Pair {
    double d;
    double u;
};

double secular(const std::vector<double>& d,
               const std::vector<double>& u,
               double lambda)
{
    double sum = 1.0;

    for (std::size_t i = 0; i < d.size(); ++i) {
        sum += (u[i] * u[i]) / (d[i] - lambda);
    }

    return sum;
}

}

std::vector<double> rank1Eigenvalues(std::vector<double> d,
                                      std::vector<double> u,
                                      double tol,
                                      int maxIter)
{
    const std::size_t n = d.size();

    if (n == 0) {
        return {};
    }

    if (u.size() != n) {
        throw std::invalid_argument("d and u must have same size");
    }

    std::vector<Pair> pairs(n);

    for (std::size_t i = 0; i < n; ++i) {
        pairs[i] = {d[i], u[i]};
    }

    std::sort(pairs.begin(), pairs.end(),
              [](const Pair& a, const Pair& b) {
                  return a.d < b.d;
              });

    for (std::size_t i = 0; i < n; ++i) {
        d[i] = pairs[i].d;
        u[i] = pairs[i].u;
    }

    std::vector<double> lambda(n);

    for (std::size_t k = 0; k < n; ++k) {
        double left;
        double right;

        if (k < n - 1) {
            left  = std::nextafter(d[k], d[k + 1]);
            right = std::nextafter(d[k + 1], d[k]);
        } else {
            left = std::nextafter(d[n - 1], d[n - 1] + 1.0);
            right = d[n - 1] + 1.0;

            while (secular(d, u, right) < 0.0) {
                right = d[n - 1] + 2.0 * (right - d[n - 1]);
            }
        }

        double fLeft = secular(d, u, left);
        double fRight = secular(d, u, right);

        if (!(fLeft < 0.0 && fRight > 0.0)) {
            throw std::runtime_error("Could not bracket eigenvalue");
        }

        double mid = 0.0;

        for (int iter = 0; iter < maxIter; ++iter) {
            mid = 0.5 * (left + right);

            double fMid = secular(d, u, mid);

            if (std::abs(fMid) < tol || std::abs(right - left) < tol) {
                break;
            }

            if (fMid < 0.0) {
                left = mid;
            } else {
                right = mid;
            }
        }

        lambda[k] = mid;
    }

    return lambda;
}