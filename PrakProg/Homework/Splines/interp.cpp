#include "interp.h"
#include <cassert>

int binsearch(const std::vector<double>& x, double z) {
    assert(x.size() >= 2);
    assert(x.front() <= z && z <= x.back());

    int i = 0;
    int j = x.size() - 1;

    while (j - i > 1) {
        int mid = (i + j) / 2;
        if (z > x[mid]) i = mid;
        else j = mid;
    }

    return i;
}

double linterp(const std::vector<double>& x,
               const std::vector<double>& y,
               double z) {
    assert(x.size() == y.size());
    assert(x.size() >= 2);

    int i = binsearch(x, z);

    double dx = x[i+1] - x[i];
    assert(dx > 0);

    double dy = y[i+1] - y[i];

    return y[i] + dy / dx * (z - x[i]);
}

double linterpInteg(const std::vector<double>& x,
                    const std::vector<double>& y,
                    double z) {
    assert(x.size() == y.size());
    assert(x.size() >= 2);
    assert(x.front() <= z && z <= x.back());

    int iz = binsearch(x, z);
    double sum = 0.0;

    for (int i = 0; i < iz; i++) {
        double dx = x[i+1] - x[i];
        assert(dx > 0);

        // integral over full interval = trapezoid area
        sum += 0.5 * (y[i] + y[i+1]) * dx;
    }

    // partial interval from x[iz] to z
    double dx = x[iz+1] - x[iz];
    double slope = (y[iz+1] - y[iz]) / dx;
    double dz = z - x[iz];

    sum += y[iz] * dz + 0.5 * slope * dz * dz;

    return sum;
}