#include "quadspline.h"
#include "interp.h"
#include <cassert>

qspline::qspline(const std::vector<double>& xs,
                 const std::vector<double>& ys)
    : x(xs), y(ys)
{
    int n = x.size();
    b.resize(n-1);
    c.resize(n-1);

    // her beregnes b og c
}

double qspline::eval(double z) const {
    int i = binsearch(x, z);
    double dx = z - x[i];
    return y[i] + b[i]*dx + c[i]*dx*dx;
}

double qspline::deriv(double z) const {
    int i = binsearch(x, z);
    double dx = z - x[i];
    return b[i] + 2*c[i]*dx;
}

double qspline::integ(double z) const {
    int i = binsearch(x, z);
    double sum = 0;

    for(int k = 0; k < i; k++) {
        double dx = x[k+1] - x[k];
        sum += y[k]*dx
             + 0.5*b[k]*dx*dx
             + c[k]*dx*dx*dx/3.0;
    }

    double dx = z - x[i];
    sum += y[i]*dx
         + 0.5*b[i]*dx*dx
         + c[i]*dx*dx*dx/3.0;

    return sum;
}