#include "cubespline.h"
#include "interp.h"

#include <cassert>
#include <vector>

cspline::cspline(const std::vector<double>& xs,
                 const std::vector<double>& ys)
    : x(xs), y(ys)
{
    int n = x.size();
    assert(n > 1);

    b.resize(n-1);
    c.resize(n);
    d.resize(n-1);

    std::vector<double> h(n-1), p(n-1);

    for(int i = 0; i < n-1; i++) {
        h[i] = x[i+1] - x[i];
        assert(h[i] > 0);
        p[i] = (y[i+1] - y[i]) / h[i];
    }

    std::vector<double> D(n), Q(n-1), B(n);

    D[0] = 2;
    B[0] = 3*p[0];

    for(int i = 1; i < n-1; i++) {
        D[i] = 2*h[i-1]/h[i] + 2;
        Q[i] = h[i-1]/h[i];
        B[i] = 3*(p[i-1] + p[i]*h[i-1]/h[i]);
    }

    D[n-1] = 2;
    B[n-1] = 3*p[n-2];

    // forward elimination
    for(int i = 1; i < n; i++) {
        D[i] -= Q[i-1]/D[i-1];
        B[i] -= B[i-1]/D[i-1];
    }

    // back substitution
    c[n-1] = B[n-1]/D[n-1];

    for(int i = n-2; i >= 0; i--) {
        c[i] = (B[i] - Q[i]*c[i+1]) / D[i];
    }

    for(int i = 0; i < n-1; i++) {
        b[i] = p[i] - h[i]*(2*c[i] + c[i+1])/3.0;
        d[i] = (c[i+1] - c[i])/(3*h[i]);
    }
}

double cspline::eval(double z) const {
    int i = binsearch(x, z);
    double dx = z - x[i];

    return y[i]
         + b[i]*dx
         + c[i]*dx*dx
         + d[i]*dx*dx*dx;
}

double cspline::deriv(double z) const {
    int i = binsearch(x, z);
    double dx = z - x[i];

    return b[i]
         + 2*c[i]*dx
         + 3*d[i]*dx*dx;
}

double cspline::integ(double z) const {
    int i = binsearch(x, z);
    double sum = 0;

    for(int k = 0; k < i; k++) {
        double dx = x[k+1] - x[k];

        sum += y[k]*dx
             + b[k]*dx*dx/2.0
             + c[k]*dx*dx*dx/3.0
             + d[k]*dx*dx*dx*dx/4.0;
    }

    double dx = z - x[i];

    sum += y[i]*dx
         + b[i]*dx*dx/2.0
         + c[i]*dx*dx*dx/3.0
         + d[i]*dx*dx*dx*dx/4.0;

    return sum;
}