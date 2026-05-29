#include "ODE.h"
#include <cmath>
#include <algorithm>

vec operator+(const vec& a, const vec& b) {
    vec c(a.size());
    for(size_t i=0;i<a.size();i++) c[i]=a[i]+b[i];
    return c;
}

vec operator-(const vec& a, const vec& b) {
    vec c(a.size());
    for(size_t i=0;i<a.size();i++) c[i]=a[i]-b[i];
    return c;
}

vec operator*(double s, const vec& a) {
    vec c(a.size());
    for(size_t i=0;i<a.size();i++) c[i]=s*a[i];
    return c;
}

double norm(const vec& v) {
    double sum=0;
    for(double x:v) sum+=x*x;
    return std::sqrt(sum);
}

std::tuple<vec, vec> rkstep45(odefun f, double x, const vec& y, double h) {
    vec k1 = f(x, y);
    vec k2 = f(x+h/4, y + h*(0.25*k1));
    vec k3 = f(x+3*h/8, y + h*(3.0/32*k1 + 9.0/32*k2));
    vec k4 = f(x+12*h/13, y + h*(1932.0/2197*k1 -7200.0/2197*k2 +7296.0/2197*k3));
    vec k5 = f(x+h, y + h*(439.0/216*k1 -8*k2 +3680.0/513*k3 -845.0/4104*k4));
    vec k6 = f(x+h/2, y + h*(-8.0/27*k1 +2*k2 -3544.0/2565*k3 +1859.0/4104*k4 -11.0/40*k5));

    vec yh = y + h*(16.0/135*k1 +6656.0/12825*k3 +28561.0/56430*k4 -9.0/50*k5 +2.0/55*k6);
    vec yl = y + h*(25.0/216*k1 +1408.0/2565*k3 +2197.0/4104*k4 -1.0/5*k5);

    vec err = yh - yl;

    return {yh, err};
}

std::tuple<std::vector<double>, std::vector<vec>> driver(
    odefun f,
    double a,
    const vec& ya,
    double b,
    double h,
    double acc,
    double eps
) {
    double x = a;
    vec y = ya;

    std::vector<double> xs = {x};
    std::vector<vec> ys = {y};

    while(x < b) {
        if(x+h > b) h = b-x;

        auto [yh, err] = rkstep45(f, x, y, h);

        double tol = (acc + eps*norm(yh))*std::sqrt(h/(b-a));
        double e = norm(err);

        if(e <= tol) {
            x += h;
            y = yh;
            xs.push_back(x);
            ys.push_back(y);
        }

        if(e > 0)
            h *= std::min(std::pow(tol/e,0.25)*0.95,2.0);
        else
            h *= 2;
    }

    return {xs, ys};
}